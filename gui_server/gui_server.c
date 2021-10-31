#include "gui_server.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define _GNU_SOURCE
#include <sys/socket.h>

int tty0_fd, fbfd = 0, kbfd = 0, msfd = 0, page = 0, prevPage = 1;
struct fb_var_screeninfo *vinfo;
struct fb_fix_screeninfo *finfo;
long int screensize = 0, rowsize = 0, mmapsize = 0;
char *fbp = 0, *keyboardDeviceName = 0, *tmpStr;
struct stat *st;
uint8_t old_leftBtn, old_rightBtn, old_midBtn, shiftDown, ctrlDown;
uint32_t mouseX = 0, mouseY = 0, mouseDownAtX = 0, mouseDownAtY = 0, mouseUpAtX = 0, mouseUpAtY = 0, mouseMoved = 0;
uint32_t underCursorX = 0, underCursorY = 0, mouseWentDown = 0, mouseWentUp = 0, keyWentDown = 0, keyWentUp = 0;
uint32_t mouseIsDown = 0;
uint8_t keysDown[NUM_KEYS_CHECKED], prevKeysDown[NUM_KEYS_CHECKED];
uint64_t shiftUpTimeNanos = 0, ctrlUpTimeNanos;
uint32_t underCursor[CURSOR_SIZE][CURSOR_SIZE];
uint32_t foregroundColor = 0x000000FF, backgroundColor = 0xFFFFFF;
uint8_t *close_box_img2, *next_arrow_img2, *arch_logo_img2;
int server_sockfd;
unsigned int totalMessageIdx = 0, returnMessageIdx = 0;
char *totalMessage = NULL, *returnMessage = NULL;
int client_sockfd, t;
struct sockaddr_un remote, local;
char buff[1024];
unsigned int i, len, expectedMsgLen = 0;
void segfaultSigaction(int signal, siginfo_t *si, void *arg) {
    printf("Caught segfault at address %p\n", si->si_addr); ExitWithError("Segfault");
}
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
void DrawPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
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
    int i;
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
        if (fbp != (void *)-1) { break; }
    }
}
int OpenKeyboard() {
    DIR *d;
    struct dirent *dir;
    int res;
    char *kbLink = 0, *kbPath = 0;
    d = opendir("/dev/input/by-path");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, "event-kbd") != NULL) { // TODO: What if more than one keyboard?
                kbLink = malloc(256);
                kbPath = malloc(256);
                sprintf(kbLink, "/dev/input/by-path/%s", dir->d_name);
                char *realpathRes = realpath(kbLink, kbPath);
                if (realpathRes == (char *)NULL) { perror("ERror getting realpath of kbd device symlink"); exit(10); }
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
                if (a > 128) { DrawPixel(mouseX + x, mouseY + y, r, g, b); }
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
    unsigned long xCharPos = 0, yCharPos = 0, glyphIdx, glyphRow, charIdx, len, j, x2, y2, c, i;
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
void DrawRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    int i, j, xx, yy;
    for (j = 0; j < h; j++) { for (i = 0; i < w; i++) {
        xx = x + i; yy = y + j;
        if (xx < vinfo->xres && yy < vinfo->yres) {
            DrawPixel(xx, yy, (foregroundColor >> 16) & 0xFF, (foregroundColor >> 8) & 0xFF, foregroundColor & 0xFF);
        }
    } }
}
void ClearScreen() {
    uint32_t x, y;
    for (x = 0; x < vinfo->xres; x++) { for (y = 0; y < vinfo->yres; y++) { DrawPixel(x, y, 0x00, 0xFF, 0xFF); }}
}
uint8_t * LoadBitmap(const char *path) {
    int x, y, n;
    uint32_t i, j, offset;
    uint8_t *bmp = stbi_load(path, &x, &y, &n, 4), *tmp; // 4: Always try to get RGBA format
    printf("Loaded bitmap %s w=%d h=%d bpp=%d\n", path, x, y, n);
    return bmp;
}
void FreeBitmap(uint8_t *bmp) {
    stbi_image_free(bmp);
}
void DrawBitmap(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t *bmp) {
    printf("Drawing bitmap w=%d h=%d size=%d addr=%08lx\n", w, h, w * h * 4, (uint64_t)bmp);
    uint32_t i, j, offset;
    for (i = 0; i < w; i++) { for (j = 0; j < h; j++) {
        offset = ((j * w) + i) * (vinfo->bits_per_pixel / 8);
        DrawPixel(x + i, y + j, bmp[offset], bmp[offset + 1], bmp[offset + 2]);
    } }
}
void DrawArchLogo(uint32_t x, uint32_t y) {
    DrawBitmap(x, y, 65, 65, arch_logo_img2);
}
void DrawCloseBox() {
    uint8_t pressed = mouseIsDown && (mouseDownAtX >= (vinfo->xres - 32)) && mouseDownAtY < 32;
    DrawBitmap(vinfo->xres - 32, 0, 32, 32, pressed ? close_box_img2 : close_box_img2);
}
void DrawNextArrow() {
    uint8_t pressed = mouseIsDown && (mouseDownAtX >= (vinfo->xres - 32)) && mouseDownAtY >= (vinfo->yres - 32);
    DrawBitmap(vinfo->xres - 32, vinfo->yres - 32, 32, 32, pressed ? next_arrow_img2 : next_arrow_img2);
}
void Cleanup() {
    munmap(fbp, screensize);
    stop_server();
    close(fbfd);
}
uint32_t MouseDownAndUpWithinRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    return (mouseDownAtX >= x && mouseDownAtX < (x + w) && mouseDownAtY >= y && mouseDownAtY < (y + h) &&
        mouseUpAtX >= x && mouseUpAtX < (x + w) && mouseUpAtY >= y && mouseUpAtY < (y + h));
}
void ExitNormally() {
    while (getchar() != EOF) {}
    ioctl(tty0_fd, KDSETMODE, KD_TEXT);
    Cleanup();
    printf("Exiting normally\n");
    exit(0);
}
void ExitWithError(char *msg) {
    int oldErrno = errno;
    while (getchar() != EOF) {}
    ioctl(tty0_fd, KDSETMODE, KD_TEXT);
    Cleanup();
    printf("Error: %s. Exiting with error: %d (%s)\n", msg, oldErrno, strerror(oldErrno));
    exit(2);
}
void DoPage() {
    uint8_t changedPage = prevPage != page;
    uint32_t redraw = changedPage || mouseWentDown || mouseWentUp;
    prevPage = page;
    if (redraw) {
        RestoreUnderCursor();
        ClearScreen();
    }
    switch (page) {
        case 0: {
            if (mouseWentUp) {
                if (MouseDownAndUpWithinRect(vinfo->xres - 32, 0, 32, 32)) { ExitNormally(); } // Close button clicked
                else if (MouseDownAndUpWithinRect(vinfo->xres - 32, vinfo->yres - 32, 32, 32)) { page++; }
            }
            if (changedPage) {
                // GetPartitions();
            }
            if (redraw) {
                sprintf(tmpStr, "Welcome");
                DrawText(0, 0, tmpStr);
                DrawArchLogo(0, 24);
            }
            break;
        }
        case 1: {
            if (mouseWentUp) {
                if (MouseDownAndUpWithinRect(vinfo->xres - 32, 0, 32, 32)) { ExitNormally(); } // Close button clicked
                else if (MouseDownAndUpWithinRect(vinfo->xres - 32, vinfo->yres - 32, 32, 32)) { page++; }
            }
            if (redraw) {
                sprintf(tmpStr, "Step 1 of %d - Choose Boot Drive", NUM_STEPS);
                DrawText(0, 0, tmpStr);
            }
            break;
        }
        case 2: {
            if (mouseWentUp) {
                if (MouseDownAndUpWithinRect(vinfo->xres - 32, 0, 32, 32)) { ExitNormally(); } // Close button clicked
                else if (MouseDownAndUpWithinRect(vinfo->xres - 32, vinfo->yres - 32, 32, 32)) { page++; }
            }
            if (redraw) {
                sprintf(tmpStr, "Step 2 of %d - Choose Keyboard Layout", NUM_STEPS);
                DrawText(0, 0, tmpStr);
            }
            break;
        }
        case 3: {
            if (mouseWentUp) {
                if (MouseDownAndUpWithinRect(vinfo->xres - 32, 0, 32, 32)) { ExitNormally(); } // Close button clicked
                else if (MouseDownAndUpWithinRect(vinfo->xres - 32, vinfo->yres - 32, 32, 32)) { page++; }
            }
            if (redraw) {
                sprintf(tmpStr, "Step 3 of %d - Connect to Network", NUM_STEPS);
                DrawText(0, 0, tmpStr);
            }
            break;
        }
        default: {
            if (mouseWentUp) {
                if (MouseDownAndUpWithinRect(vinfo->xres - 32, 0, 32, 32)) { ExitNormally(); } // Close button clicked
            }
            if (redraw) {
                RestoreUnderCursor();
                ClearScreen();
                SaveUnderCursor();
            }
            break;
        }
    }
    int socketReadRes = ReadFromSocket();
    if (socketReadRes) {
        HandleMessage();
        send(client_sockfd, totalMessage, totalMessageIdx, 0);
        close(client_sockfd);
        printf("Done handling\n");
        fflush(stdout);
    }
    if (redraw) { // TODO: Finer-grained redraw flags. Don't need to redraw entire page to redraw the closebox...
        DrawCloseBox();
        DrawNextArrow();
        SaveUnderCursor();
    }
}
void EnableGraphicsMode() {
    struct termios newt;
    newt.c_lflag = 0;//&= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    printf("\f");
    int t = -1;
    tty0_fd = open("/dev/tty0", O_WRONLY, 0);
    ioctl(tty0_fd, KDSETMODE, KD_GRAPHICS);
}
void HandleMessage() {
    returnMessageIdx = 0;
    char *tm = totalMessage;
    int idx = 4;
    int numSubmessages = ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8));
    while (1) {
        int returned = 0;
        int subMsgCode = ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8));
        switch (subMsgCode) {
            case MSG_CLEAR_SCREEN: { ClearScreen(); break; }
            case MSG_SET_FGCOLOR: { SetFGColor(tm[idx++], tm[idx++], tm[idx++]); break; }
            case MSG_SET_BGCOLOR: { SetBGColor(tm[idx++], tm[idx++], tm[idx++]); break; }
            case MSG_DRAW_RECT: {
                DrawRect(((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8)),
                         ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8)),
                         ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8)),
                         ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8)));
                break; }
            case MSG_LOAD_BITMAP: {
                char *bmp = LoadBitmap(&(tm[idx]));
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp) & 0xff;
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp >> 8) & 0xff;
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp >> 16) & 0xff;
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp >> 24) & 0xff;
                returned = 1;
                break; }
            case MSG_DRAW_BITMAP: {
                DrawBitmap(((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8)),
                         ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8)),
                         ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8)),
                         ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8)),
                         (char *)((uint64_t)tm[idx++] | ((uint64_t)tm[idx++] << 8) |
                             ((uint64_t)tm[idx++] << 16) | ((uint64_t)tm[idx++] << 24)));
                break; }
            case MSG_DRAW_TEXT: {
                DrawText(
                    ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8)),
                    ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8)),
                    (char *)(&(tm[idx]))
                );
                idx += strlen(&(tm[idx]));
                break;
        }
        if (!returned) {
            returnMessage[returnMessageIdx++ + 4] = 1; // Append default "OK" message to return buffer
        }
        memcpy(totalMessage, returnMessage, returnMessageIdx);
        totalMessage[0] = (returnMessageIdx & 0xFF);
        totalMessage[1] = ((returnMessageIdx >> 8) & 0xFF);
        totalMessage[2] = ((returnMessageIdx >> 16) & 0xFF);
        totalMessage[3] = ((returnMessageIdx >> 24) & 0xFF);
    }
}
int ReadFromSocket() {
    t = sizeof(remote);
    int acceptRes = accept4(server_sockfd, (struct sockaddr *)&remote, &t, SOCK_NONBLOCK);
    if (acceptRes == -1) {
        if (errno != EWOULDBLOCK && errno != EAGAIN) { perror("accept"); exit(1); }
        return 0;
    }
    client_sockfd = acceptRes;
    totalMessageIdx = 0;
    memset(totalMessage, 0, MAX_MESSAGE_SIZE);
    while(len = recv(client_sockfd, &buff, 1024, 0), len > 0) {
        memcpy(&(totalMessage[totalMessageIdx]), buff, len);
        totalMessageIdx += len;
        if (expectedMsgLen == 0 && totalMessageIdx >= 4) {
            expectedMsgLen = (unsigned int)totalMessage[0] + ((unsigned int)totalMessage[1] << 8) +
                            ((unsigned int)totalMessage[2] << 16) + ((unsigned int)totalMessage[3] << 24);
        }
        if (expectedMsgLen != 0 && totalMessageIdx >= expectedMsgLen + 4) {
            totalMessage[expectedMsgLen + 4] = 0;
            break;
        }
    }
    return 1;
}
void SetupSocket() {
    totalMessage = malloc(MAX_MESSAGE_SIZE); 
    returnMessage = malloc(MAX_MESSAGE_SIZE); 
    if((server_sockfd = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0)) == -1) { perror("Error creating server socket"); exit(1); }
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if(bind(server_sockfd, (struct sockaddr *)&local, len) == -1) { perror("binding"); exit(1); }
    if (listen(server_sockfd, 5) == -1) { perror("listen"); exit(1); }
    printf("Listening...\n");
    fflush(stdout);
}
void stop_server() {
    unlink(SOCK_PATH);
    kill(0, SIGKILL);
    exit(0);
}
int main(int argc, char *argv[]) {
    struct termios oldt, newt;
    struct pollfd *pfds;
    struct input_event *evt;
    ssize_t siz;
    char *buff;
    int ready, x, y, ppid, pid, i;
    uint8_t xdir, ydir, leftBtn, rightBtn, midBtn, temp;
    int8_t xdiff, ydiff;
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfaultSigaction;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);
    buff = malloc(65536);
    tmpStr = malloc(65536);
    pfds = calloc(2, sizeof(struct pollfd));
    arch_logo_img2 = LoadBitmap("bundle/images/archlogo65.png");
    close_box_img2 = LoadBitmap("bundle/images/closebox32.png");
    next_arrow_img2 = LoadBitmap("bundle/images/nextarrow32.png");
    signal(SIGTERM, stop_server);
    SetupSocket();
    OpenFramebuffer();
    EnableGraphicsMode();
    // newt.c_lflag = 0;//&= ~(ICANON | ECHO);
    // tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    // printf("\f");
    for (x = 0; x < vinfo->xres; x++) { for (y = 0; y < vinfo->yres; y++) { DrawPixel(x, y, 0x00, 0xFF, 0xFF); }}
    // for (i = 0; i < 600; i++) { DrawPixel(i, i, 0xFF, 0xFF, 0xFF); }
    // DrawText(0, 0, "Hello, there!");
    // DrawArchLogo(200, 200);
    ClearScreen();
    SaveUnderCursor();
    kbfd = OpenKeyboard();
    msfd = OpenMouse();
    pfds[0].fd = kbfd; pfds[0].events = POLLIN;
    pfds[1].fd = msfd; pfds[1].events = POLLIN;
    while (1) {
        mouseWentDown = 0;
        mouseWentUp = 0;
        keyWentDown = 0;
        keyWentUp = 0;
        mouseMoved = 0;
        ready = poll(pfds, 2, 30);
        if (ready == -1) { perror("poll() returned -1");exit(9); }
        if (pfds[0].revents != 0) {
            if (pfds[0].revents & POLLIN) {
                siz = read(pfds[0].fd, buff, 65536);
                if (siz == -1) { perror("Problem reading from kbfd"); exit(8); }
                evt = (struct input_event *)buff;
                for (i = 0, evt = (struct input_event *)buff; i < siz; i += sizeof(struct input_event), evt++) {
                    if (evt->type == EV_KEY) {
                        if (evt->code >= BTN_MOUSE && evt->code < BTN_JOYSTICK) {} // mouse click: ignore
                        else { // Keyboard key
                            if (evt->value == 1) {
                                keyWentDown = 1;
                                if (evt->code == 42 || evt->code == 54) { shiftDown = 1; }
                                if (evt->code == 29 || evt->code == 97) { ctrlDown = 1; }
                                for (i = 0; i < NUM_KEYS_CHECKED; i++) { prevKeysDown[i] = keysDown[i]; }
                                keysDown[evt->value] = 1;
                            } else if (evt->value == 0) {
                                keyWentUp = 1;
                                for (i = 0; i < NUM_KEYS_CHECKED; i++) { prevKeysDown[i] = keysDown[i]; }
                                keysDown[evt->value] = 0;
                                temp = ctrlDown || (get_nsecs() < (ctrlUpTimeNanos + MOD_LINGER_NANOS));
                                if (evt->code == 16 && temp) { ExitNormally(); } // ctrl-q quits
                                if (evt->code == 42 || evt->code == 54) {
                                    shiftDown = 0;
                                    shiftUpTimeNanos = get_nsecs();
                                }
                                if (evt->code == 29 || evt->code == 97) {
                                    ctrlDown = 0;
                                    ctrlUpTimeNanos = get_nsecs();
                                }
                            } else if (evt->value == 2) {} // Key repeat: ignore for now
                        }
                    }
                }
            }
        }
        if (pfds[1].revents != 0) {
            // There's a mouse event
            if (pfds[1].revents & POLLIN) {
                siz = read(pfds[1].fd, buff, 65536);
                if (siz == -1) { perror("Problem reading from msfd"); exit(8); }
                leftBtn = buff[0] & 1; rightBtn = (buff[0] >> 1) & 1; midBtn = (buff[0] >> 1) & 1;
                xdiff = (int8_t)buff[1]; ydiff = (int8_t)buff[2];
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
                    mouseMoved = 1;
                }
                if (old_leftBtn != leftBtn) {
                    if (leftBtn) { // Mouse down
                        mouseDownAtX = mouseX;
                        mouseDownAtY = mouseY;
                        mouseWentDown = 1;
                        mouseIsDown = 1;
                    } else { // Mouse up
                        mouseUpAtX = mouseX;
                        mouseUpAtY = mouseY;
                        mouseWentUp = 1;
                        mouseIsDown = 0;
                    }
                }
                old_leftBtn = leftBtn;
                old_rightBtn = rightBtn;
                old_midBtn = midBtn;
            }
        }
        DoPage();
        usleep(3000);
    }
    Cleanup();
    return 0;
}
