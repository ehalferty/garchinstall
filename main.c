#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "main.h"
#include "keycode_names.h"
#include "cursor.h"
#include "font.h"
#include "arch_logo.h"

#define MOD_LINGER_NANOS 100000000 // How many nanoseconds modifier keys remain down after the user lifts them
#define CURSOR_SIZE 24

int fbfd = 0, x = 0, y = 0, i = 0, j = 0, kbfd = 0, msfd = 0, stdoutfd;
struct fb_var_screeninfo *vinfo;
struct fb_fix_screeninfo *finfo;
long int screensize = 0, rowsize = 0, temp = 0, top = 0, left = 0, w = 0, h = 0, s = 0, mmapsize = 0;
char *fbp = 0;
struct stat *st;
const int PADDING = 4096;
char *keyboardDeviceName = 0;
uint8_t old_leftBtn, old_rightBtn, old_midBtn, shiftDown, ctrlDown;
uint32_t mouseX, mouseY, mouseClickedAtX, mouseClickedAtY, underCursorX, underCursorY;
uint64_t shiftUpTimeNanos = 0, ctrlUpTimeNanos;
uint32_t underCursor[CURSOR_SIZE][CURSOR_SIZE];
uint32_t foregroundColor = 0x000000FF, backgroundColor = 0xFFFFFF;

unsigned long get_nsecs() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000UL + ts.tv_nsec;
};

uint32_t PixelColor(uint8_t r, uint8_t g, uint8_t b) {
    return (r<<vinfo->red.offset) | (g<<vinfo->green.offset) | (b<<vinfo->blue.offset);
}
uint32_t GetFBOffset(uint32_t x, uint32_t y) {
    return (x + vinfo->xoffset) * (vinfo->bits_per_pixel / 8) + (y + vinfo->yoffset) * finfo->line_length;
}
void DrawPixel(uint32_t x2, uint32_t y2, uint8_t r, uint8_t g, uint8_t b) {
    uint32_t fb_offset = GetFBOffset(x, y);
    if (x >= vinfo->xres || y >= vinfo->yres || (fb_offset + 3) > mmapsize) { return; }
    *((uint32_t *)((uint64_t)fbp + fb_offset)) = PixelColor(r, g, b);
}
void DrawPixel32U(uint32_t x, uint32_t y, uint32_t c) {
    uint32_t fb_offset = GetFBOffset(x, y);
    if (x >= vinfo->xres || y >= vinfo->yres || (fb_offset + 3) > mmapsize) { return; }
    *((uint32_t *)((uint64_t)fbp + fb_offset)) = c;
}
uint32_t GetPixel(uint32_t x, uint32_t y) {
    return *((uint32_t *)((uint64_t)fbp + GetFBOffset(x, y)));
}
void OpenFramebuffer() {
    st = malloc(sizeof(struct stat));
    vinfo = malloc(sizeof(struct fb_var_screeninfo));
    finfo = malloc(sizeof(struct fb_fix_screeninfo));
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) { perror("Error: cannot open framebuffer device"); exit(1); }
    fstat(fbfd, st);
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, finfo) == -1) { perror("Error reading fixed information"); exit(2); }
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, vinfo) == -1) { perror("Error reading variable information"); exit(3); }
    mouseX = vinfo->xres / 2;
    mouseY = vinfo->yres / 2;
    screensize = vinfo->xres * vinfo->yres * (vinfo->bits_per_pixel / 8);
    for (i = 8; i >= 0; i--) {
        if (i == 0) { perror("Error: failed to map framebuffer device to memory"); exit(4); }
        mmapsize = screensize * i;
        fbp = (char *)mmap(0, mmapsize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
        if (fbp != -1) { break; }
    }
}
int OpenKeyboard() {
    DIR *d;
    struct dirent *dir;
    int res;
    char *kbLink = 0, *kbPath = 0;
    // First, get a directory listing for /dev/input/by-path
    d = opendir("/dev/input/by-path");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            // Search for results containing "event-kbd"
            if (strstr(dir->d_name, "event-kbd") != NULL) {
                // Open the first one (TODO: Eventually open all of them!)
                kbLink = malloc(256);
                kbPath = malloc(256);
                sprintf(kbLink, "/dev/input/by-path/%s", dir->d_name);
                res = realpath(kbLink, kbPath);
                if (res == 0) { perror("ERror getting realpath of kbd device symlink"); exit(10); }
                // printf("Opened kbd: %s\n", kbPath);
                res = open(kbPath, O_RDONLY);
                if (res == -1) {
                    sprintf(kbPath, "Error: Can't open %s", kbPath);
                    perror(kbPath);
                    exit(7);
                }
                closedir(d);
                return res;
            }
        }
    }
    closedir(d);
    perror("Error: Couldn't find keyboard device"); exit(6);
    return -1;
}
int OpenMouse() {
    int res = open("/dev/input/mice", O_RDONLY);
    if (res == -1) { perror("Error: Can't open /dev/input/mice"); exit(5); }
    return res;
}
void SaveUnderCursor() {
    unsigned int x, y, location;
    for (y = 0; y < CURSOR_SIZE; y++) { for (x = 0; x < CURSOR_SIZE; x++) {
        if (x + mouseX < vinfo->xres && y + mouseY < vinfo->yres) {
            underCursor[y][x] = GetPixel(x + mouseX, y + mouseY);
        }
    } }
    underCursorX = mouseX;
    underCursorY = mouseY;
}
void RestoreUnderCursor() {
    unsigned int x, y, location;
    for (y = 0; y < CURSOR_SIZE; y++) { for (x = 0; x < CURSOR_SIZE; x++) {
        if (x + underCursorX < vinfo->xres && y + underCursorY < vinfo->yres) {
            DrawPixel32U(x + underCursorX, y + underCursorY, underCursor[y][x]);
        }
    } }
}
void DrawCursor() {
    unsigned int x, y, location;
    for (y = 0; y < CURSOR_SIZE; y++) {
        for (x = 0; x < CURSOR_SIZE; x++) {
            if (x + mouseX < vinfo->xres && y + mouseY < vinfo->yres) {
                unsigned char r = cursor[((y * 24 + x) * 4)];
                unsigned char g = cursor[((y * 24 + x) * 4) + 1];
                unsigned char b = cursor[((y * 24 + x) * 4) + 2];
                unsigned char a = cursor[((y * 24 + x) * 4) + 3];
                if (a > 128) {
                    DrawPixel(mouseX + x, mouseY + y, r, g, b);
                    // location = (mouseX + x + vinfo->xoffset) * (vinfo->bits_per_pixel/8) +
                    //            (mouseY + y + vinfo->yoffset) * finfo->line_length;
                    
                    // *((uint32_t *)(fb->screen_base + location)) = kmm_pixelColor(r, g, b, vinfo);
                }
            }
        }
    }
}
void SetBGColor(uint8_t r, uint8_t g, uint8_t b) {
    backgroundColor = ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}
void SetFGColor(uint8_t r, uint8_t g, uint8_t b) {
    foregroundColor = ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}
void DrawText(uint32_t x, uint32_t y, char *str) {
    unsigned long xCharPos = 0, yCharPos = 0, glyphIdx, glyphRow, charIdx, len, j, x2, y2, c;
    len = strlen(str);
    for (charIdx = 0; charIdx < len; charIdx++) {
        if (str[charIdx] >= 32 && str[charIdx] < 128) { // Check if printable
            // Find the character in the font sheet
            for (glyphIdx = 0; glyphIdx < NUM_FONT_GLYPHS; glyphIdx++) {
                if (font_glyph_encodings[glyphIdx] == str[charIdx]) { break; }
            }
            for (j = 0; j < 16; j++) { for (i = 0; i < 16; i++) {
                x2 = x + i + (xCharPos * FONT_WIDTH_INCLUDING_PADDING);
                y2 = y + j + (yCharPos * FONT_HEIGHT_INCLUDING_PADDING);
                glyphRow = font_glyph_bitmaps[glyphIdx * 32 + (j * 2) + 1];
                glyphRow |= (font_glyph_bitmaps[glyphIdx * 32 + (j * 2)] & 0xFF) << 8;
                c = ((glyphRow >> (16 - i)) & 1) ? foregroundColor : backgroundColor;
                DrawPixel(x2, y2, (c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
            } }
            xCharPos++;
        } else if (str[charIdx] == '\n') {
            xCharPos = 0;
            yCharPos++;
        }
    }
}
void DrawBitmap(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t *bmp) {
    uint32_t i, j, offset;
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            offset = ((j * w) + i) * (vinfo->bits_per_pixel / 8);
            DrawPixel(x + i, y + j, bmp[offset + 2], bmp[offset + 1], bmp[offset]);
        }
    }
}
void DrawArchLogo(uint32_t x, uint32_t y) {
    DrawBitmap(x, y, ARCH_LOGO_WIDTH, ARCH_LOGO_HEIGHT, arch_logo);
}
void Cleanup() {
    munmap(fbp, screensize);
    close(fbfd);
}
int main(int argc, char *argv[]) {
    struct termios oldt, newt;
    struct pollfd *pfds;
    ssize_t siz;
    char *buff;
    int ready, xx, yy, ppid, pid, i, qKeycode;
    struct input_event *evt;
    uint8_t xdir, ydir, leftBtn, rightBtn, midBtn, temp;
    int8_t xdiff, ydiff;
    printf("argv0=%s\n", argv[0]);
    qKeycode = key_name_to_keycode("Q");
    buff = malloc(65536);
    pfds = calloc(2, sizeof(struct pollfd));
    OpenFramebuffer();
    newt.c_lflag = 0;//&= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    printf("\f");
    for (xx = 0; xx < vinfo->xres; xx++) { //, 
        for (yy = 0; yy < vinfo->yres; yy++) {
            DrawPixel(xx, yy, 0x00, 0xFF, 0xFF);
        }
    }
    for (i = 0; i < 600; i++) {
        DrawPixel(i, i, 0xFF, 0xFF, 0xFF);
    }
    DrawText(0, 0, "Hello, there!");
    DrawArchLogo(200, 200);
    SaveUnderCursor();
    kbfd = OpenKeyboard();
    msfd = OpenMouse();
    pfds[0].fd = kbfd;
    pfds[0].events = POLLIN;
    pfds[1].fd = msfd;
    pfds[1].events = POLLIN;
    // printf("kbfd=%d, msfd=%d\n", kbfd, msfd);
    while (1) {
        ready = poll(pfds, 2, 30);
        if (ready == -1) {
            perror("poll");exit(9);
        }
        if (pfds[0].revents != 0) {
            // There's a kbd event
            if (pfds[0].revents & POLLIN) {
                // printf("Reading from fd: %d buff=%08llx sizeof(buff)=%d sizeof(struct input_event)=%d\n",
                    // pfds[0].fd, (unsigned long)buff, 65536, sizeof(struct input_event));
                siz = read(pfds[0].fd, buff, 65536);
                if (siz == -1) {
                    printf("errno=%d\n", errno);
                    perror("Problem reading from kbfd"); exit(8);
                } else {
                    // printf("Read %d bytes from kbfd\n", siz);
                    evt = (struct input_event *)buff;
                    for (i = 0, evt = (struct input_event *)buff; i < siz; i += sizeof(struct input_event), evt++) {
                        if (evt->type == EV_KEY) {
                            if (evt->code >= BTN_MOUSE && evt->code < BTN_JOYSTICK) {
                                // Mouse click. Ignore?
                            } else {
                                // Keyboard key
                                if (evt->value == 1) {
                                    if (evt->code == 42 || evt->code == 54) { shiftDown = 1; }
                                    if (evt->code == 29 || evt->code == 97) { ctrlDown = 1; }
                                    // Keydown
                                    // printf("keydown\n");
                                } else if (evt->value == 0) {
                                    // Keyup
                                    // printf("keyup\n");
                                    temp = ctrlDown || (get_nsecs() < (ctrlUpTimeNanos + MOD_LINGER_NANOS));
                                    // ctrl-q quits
                                    if (evt->code == 16 && temp) {
                                        // TODO: Use this for all exit conditions
                                        while (getchar() != EOF) {}
                                        exit(20);
                                    }
                                    if (evt->code == 42 || evt->code == 54) {
                                        shiftDown = 0;
                                        shiftUpTimeNanos = get_nsecs();
                                    }
                                    if (evt->code == 29 || evt->code == 97) {
                                        ctrlDown = 0;
                                        ctrlUpTimeNanos = get_nsecs();
                                    }
                                } else if (evt->value == 2) {
                                    // Key repeat
                                }
                            }
                        }
                        // printf("Event: type=%d code=%d value=%d\n", evt->type, evt->code, evt->value);
                    }
                }
            }
        }
        if (pfds[1].revents != 0) {
            // There's a mouse event
            if (pfds[1].revents & POLLIN) {
                siz = read(pfds[1].fd, buff, 65536);
                if (siz == -1) {
                    perror("Problem reading from msfd"); exit(8);
                } else {
                    // xdir = (buff[0] >> 4) & 1;
                    // ydir = (buff[0] >> 5) & 1;
                    leftBtn = buff[0] & 1;
                    rightBtn = (buff[0] >> 1) & 1;
                    midBtn = (buff[0] >> 1) & 1;
                    xdiff = (int8_t)buff[1];
                    ydiff = (int8_t)buff[2];
                    // xdir = (buff[1] >> 6) & 1;
                    // ydir = (buff[1] >> 6) & 1;
                    // xdiff = buff[1] & 0x3F;
                    // ydiff = buff[2] & 0x3F;
                    // printf("(%d, %d)\n", xdiff, ydiff);
                    if (xdiff != 0 || ydiff != 0) {
                        if (((int)mouseX + xdiff) < 0) { mouseX = 0; }
                        else if ((mouseX + xdiff) > vinfo->xres) { mouseX = vinfo->xres; }
                        else { mouseX += xdiff; }
                        if (((int)mouseY - ydiff) < 0) { mouseY = 0; }
                        else if ((mouseY - ydiff) > vinfo->yres) { mouseY = vinfo->yres; }
                        else { mouseY -= ydiff; }
                        RestoreUnderCursor();
                        SaveUnderCursor();
                        DrawCursor();
                    }
                    if (old_leftBtn != leftBtn) {
                        if (leftBtn) {
                            // Left button pressed
                            mouseClickedAtX = mouseX;
                            mouseClickedAtY = mouseY;
                        } else {
                            // Left button released
                        }
                    }
                    old_leftBtn = leftBtn;
                    old_rightBtn = rightBtn;
                    old_midBtn = midBtn;
                }
            }
        }
        usleep(3000);
    }
    Cleanup();
    return 0;
}
