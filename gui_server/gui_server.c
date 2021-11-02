#include "gui_server.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define _GNU_SOURCE
#include <sys/socket.h>

char *fbp = 0, *keyboardDeviceName = 0, *tmpStr, *totalMessage = NULL, *returnMessage = NULL;
char buff[1024];
int tty0_fd, fbfd = 0, kbfd = 0, msfd = 0, page = 0, prevPage = 1, server_sockfd, client_sockfd, t;
long int screensize = 0, rowsize = 0, mmapsize = 0;
struct fb_fix_screeninfo *finfo;
struct fb_var_screeninfo *vinfo;
struct sockaddr_un remote, local;
struct stat *st;
uint32_t foregroundColor = 0x000000FF, backgroundColor = 0xFFFFFF, keyThatWentDown = 0, keyThatWentUp, mouseIsDown = 0;
uint32_t mouseX = 0, mouseY = 0, mouseDownAtX = 0, mouseDownAtY = 0, mouseUpAtX = 0, mouseUpAtY = 0, mouseMoved = 0;
uint32_t underCursor[CURSOR_SIZE][CURSOR_SIZE];
uint32_t underCursorX = 0, underCursorY = 0, mouseWentDown = 0, mouseWentUp = 0, keyWentDown = 0, keyWentUp = 0;
uint64_t i, len, expectedMsgLen = 0, shiftUpTimeNanos = 0, ctrlUpTimeNanos;
uint8_t keysDown[NUM_KEYS_CHECKED], prevKeysDown[NUM_KEYS_CHECKED];
uint8_t old_leftBtn, old_rightBtn, old_midBtn, shiftDown, ctrlDown, cornerRadius = 0;
unsigned int totalMessageIdx = 0, returnMessageIdx = 0;
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
                if (font_glyph_encodings[glyphIdx] == str[charIdx]) { break; } }
            for (j = 0; j < 16; j++) { for (i = 0; i < 16; i++) {
                x2 = x + i + (xCharPos * FONT_WIDTH_INCLUDING_PADDING);
                y2 = y + j + (yCharPos * FONT_HEIGHT_INCLUDING_PADDING);
                glyphRow = font_glyph_bitmaps[glyphIdx * 32 + (j * 2) + 1];
                glyphRow |= (font_glyph_bitmaps[glyphIdx * 32 + (j * 2)] & 0xFF) << 8;
                c = ((glyphRow >> (16 - i)) & 1) ? foregroundColor : backgroundColor;
                DrawPixel(x2, y2, (c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
            } }
            xCharPos++;
        } else if (str[charIdx] == '\n') { xCharPos = 0; yCharPos++; }
    }
}
void DrawCirclePixels(uint32_t xc, uint32_t yc, uint32_t x, uint32_t y, uint32_t corner) {
    uint32_t fg = foregroundColor;
    uint8_t r = (fg >> 16) & 0xFF, g = (fg >> 8) & 0xFF, b = fg & 0xFF;
    switch (corner) {
        case 0: {
            DrawPixel(xc - x, yc - y, r, g, b);
            DrawPixel(xc - y, yc - x, r, g, b);
        break; }
        case 1: {
            DrawPixel(xc + x, yc - y, r, g, b);
            DrawPixel(xc + y, yc - x, r, g, b);
        break; }
        case 2: {
            DrawPixel(xc - x, yc + y, r, g, b);
            DrawPixel(xc + x, yc + y, r, g, b);
        break; }
        case 3: {
            DrawPixel(xc - y, yc + x, r, g, b);
            DrawPixel(xc + y, yc + x, r, g, b);
        break; }
    }
}
void DrawCircle(uint32_t xc, uint32_t yc, uint32_t r, uint32_t corner) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    DrawCirclePixels(xc, yc, x, y, corner);
    while (y >= x) {
        x++;
        if (d > 0) { y--; d = d + 4 * (x - y) + 10; }
        else { d = d + 4 * x + 6; }
        DrawCirclePixels(xc, yc, x, y, corner);
    }
}
void DrawRoundedRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t r) {
    DrawRect(x, y + r, w, h - r * 2);
    DrawRect(x + r, y, w - r * 2, r);
    DrawRect(x + r, y + h - r, w - r * 2, r);
    DrawCircle(x - 10, y - 10, r + 3, 0);
    DrawCircle(x + w + 10, y - 10, r + 3, 1);
    DrawCircle(x - 10, y + h + 10, r + 3, 2);
    DrawCircle(x + w + 10, y + h + 10, r + 3, 3);
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
    return bmp;
}
void FreeBitmap(uint8_t *bmp) {
    stbi_image_free(bmp);
}
void DrawBitmap(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t *bmp) {
    uint32_t i, j, offset;
    for (i = 0; i < w; i++) { for (j = 0; j < h; j++) {
        offset = ((j * w) + i) * (vinfo->bits_per_pixel / 8);
        DrawPixel(x + i, y + j, bmp[offset], bmp[offset + 1], bmp[offset + 2]);
    } }
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
void EnableGraphicsMode() {
    struct termios newt;
    printf("\f");
    newt.c_lflag = 0;//&= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int t = -1;
    tty0_fd = open("/dev/tty0", O_WRONLY, 0);
    ioctl(tty0_fd, KDSETMODE, KD_GRAPHICS);
}
void HandleMessage() {
    returnMessageIdx = 4;
    char *tm = totalMessage;
    int idx = 4, subMessageIdx, i, j;
    int numSubmessages = ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8));
    for (subMessageIdx = 0; subMessageIdx < numSubmessages; subMessageIdx++) {
        int returned = 0;
        int subMsgCode = ((unsigned int)tm[idx++] + ((unsigned int)tm[idx++] << 8));
        if (subMsgCode == 0) { break; }
        int needToRedrawCursor = (subMsgCode == MSG_CLEAR_SCREEN || subMsgCode == MSG_DRAW_RECT ||
            subMsgCode == MSG_DRAW_BITMAP || subMsgCode == MSG_DRAW_TEXT);
        if (needToRedrawCursor) { RestoreUnderCursor(); }
        switch (subMsgCode) {
            case MSG_CLEAR_SCREEN: { ClearScreen(); break; }
            case MSG_SET_FGCOLOR: { SetFGColor(tm[idx++], tm[idx++], tm[idx++]); break; }
            case MSG_SET_BGCOLOR: { SetBGColor(tm[idx++], tm[idx++], tm[idx++]); break; }
            case MSG_DRAW_RECT: {
                uint32_t x = (uint8_t)(tm[idx]) + ((uint8_t)(tm[idx + 1]) << 8);
                uint32_t y = (uint8_t)(tm[idx + 2]) + ((uint8_t)(tm[idx + 3]) << 8);
                uint32_t w = (uint8_t)(tm[idx + 4]) + ((uint8_t)(tm[idx + 5]) << 8);
                uint32_t h = (uint8_t)(tm[idx + 6]) + ((uint8_t)(tm[idx + 7]) << 8);
                if (cornerRadius == 0) { DrawRect(x, y, w, h); } else { DrawRoundedRect(x, y, w, h, cornerRadius); }
                idx += 8;
                break; }
            case MSG_SET_CORNER_RADIUS: {
                cornerRadius = (uint8_t)(tm[idx]);
                break; }
            case MSG_LOAD_BITMAP: {
                char *bmp = LoadBitmap(&(tm[idx]));
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp) & 0xff;
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp >> 8) & 0xff;
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp >> 16) & 0xff;
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp >> 24) & 0xff;
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp >> 32) & 0xff;
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp >> 40) & 0xff;
                returnMessage[returnMessageIdx++ + 4] = ((uint64_t)bmp >> 48) & 0xff;
                returned = 1;
                idx += strlen(&(tm[idx])) + 8; // This may be wrong lol
                break; }
            case MSG_DRAW_BITMAP: {
                for (i = 0; i < 64; i++) {
                    printf("%02x ", (uint8_t)tm[i + 8]);
                    if (i == 15 || i == 31 || i == 47 || i ==63) { printf("\n"); }
                }
                uint32_t x = (uint8_t)(tm[idx]) + ((uint8_t)(tm[idx + 1]) << 8);
                uint32_t y = (uint8_t)(tm[idx + 2]) + ((uint8_t)(tm[idx + 3]) << 8);
                uint32_t w = (uint8_t)(tm[idx + 4]) + ((uint8_t)(tm[idx + 5]) << 8);
                uint32_t h = (uint8_t)(tm[idx + 6]) + ((uint8_t)(tm[idx + 7]) << 8);
                uint64_t bmp = 0;
                for (i = 0; i < 8; i++) { bmp |= (uint64_t)((uint8_t)(tm[idx + 8 + i])) << ((uint8_t)i * 8); }
                DrawBitmap(x, y, w, h, (char *)bmp);
                idx += 12;
                break; }
            case MSG_DRAW_TEXT: {
                uint32_t x = (uint8_t)(tm[idx]) + ((uint8_t)(tm[idx + 1]) << 8);
                uint32_t y = (uint8_t)(tm[idx + 2]) + ((uint8_t)(tm[idx + 3]) << 8);
                char *str = (char *)&(tm[idx + 4]);
                DrawText(x, y, str);
                idx += strlen(&(tm[idx + 4])) + 4;
                break; }
            // Send a basic set of event data an app may need to handle user interaction
            case MSG_GET_EVENTS: {
                uint8_t shiftIsDown = shiftDown || (get_nsecs() < (shiftUpTimeNanos + MOD_LINGER_NANOS));
                uint8_t ctrlIsDown = ctrlDown || (get_nsecs() < (ctrlUpTimeNanos + MOD_LINGER_NANOS));
                returnMessage[returnMessageIdx++ + 4] = ((uint8_t)(
                    ( mouseWentDown & 0x1)      | ((mouseWentUp & 0x1) << 1) | ((keyWentDown & 0x1) << 2) |
                    ((keyWentUp & 0x1)   << 3)  | ((mouseMoved & 0x1)  << 4) | ((mouseIsDown & 0x1) << 5) |
                    ((shiftIsDown & 0x1) << 6)  | ((ctrlIsDown & 0x1)  << 7))) & 0xFF;
                returnMessage[returnMessageIdx++ + 4] = (((uint32_t)keyThatWentDown)) & 0xFF;
                returnMessage[returnMessageIdx++ + 4] = (((uint32_t)keyThatWentDown >> 8)) & 0xFF;
                returnMessage[returnMessageIdx++ + 4] = (((uint32_t)keyThatWentUp)) & 0xFF;
                returnMessage[returnMessageIdx++ + 4] = (((uint32_t)keyThatWentUp >> 8)) & 0xFF;
                returnMessage[returnMessageIdx++ + 4] = (((uint32_t)mouseX)) & 0xFF;
                returnMessage[returnMessageIdx++ + 4] = (((uint32_t)mouseX >> 8)) & 0xFF;
                returnMessage[returnMessageIdx++ + 4] = (((uint32_t)mouseY)) & 0xFF;
                returnMessage[returnMessageIdx++ + 4] = (((uint32_t)mouseY >> 8)) & 0xFF;
                returned = 1;
                mouseWentDown = 0; mouseWentUp = 0; keyWentDown = 0; keyWentUp = 0; mouseMoved = 0;
                break; }
            case MSG_GET_KEYS: {
                // Send first 256 key values (Nope)
                for (i = 0; i < 32; i++) {
                    returnMessage[returnMessageIdx++ + 4] = ((uint8_t)(
                        ((keysDown[i * 8 + 0] & 1) << 0) | ((keysDown[i * 8 + 1] & 1) << 1) |
                        ((keysDown[i * 8 + 2] & 1) << 2) | ((keysDown[i * 8 + 3] & 1) << 3) |
                        ((keysDown[i * 8 + 4] & 1) << 4) | ((keysDown[i * 8 + 5] & 1) << 5) |
                        ((keysDown[i * 8 + 6] & 1) << 6) | ((keysDown[i * 8 + 7] & 1) << 7))) & 0xff;
                }
                returned = 1;
            }
        }
        if (needToRedrawCursor) { SaveUnderCursor(); DrawCursor(); }
        if (!returned) { returnMessage[returnMessageIdx++ + 4] = 1; } // Append default "OK" message to return buffer
        returnMessageIdx += 5;
        memset(totalMessage, 0, MAX_MESSAGE_SIZE);
        memcpy(totalMessage, returnMessage, returnMessageIdx);
        totalMessage[0] = (returnMessageIdx & 0xFF);            totalMessage[1] = ((returnMessageIdx >> 8) & 0xFF);
        totalMessage[2] = ((returnMessageIdx >> 16) & 0xFF);    totalMessage[3] = ((returnMessageIdx >> 24) & 0xFF);
        totalMessageIdx = returnMessageIdx;
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
    while (len = recv(client_sockfd, &buff, 1024, 0), (int)len > 0) {
        memcpy(&(totalMessage[totalMessageIdx]), buff, len);
        totalMessageIdx += len;
        if (expectedMsgLen == 0 && totalMessageIdx >= 4) {
            expectedMsgLen = (unsigned int)totalMessage[0] + ((unsigned int)totalMessage[1] << 8) +
                            ((unsigned int)totalMessage[2] << 16) + ((unsigned int)totalMessage[3] << 24);
        }
        if (expectedMsgLen != 0 && totalMessageIdx >= expectedMsgLen + 4) { break; }
    }
    return 1;
}
void SetupSocket() {
    totalMessage = malloc(MAX_MESSAGE_SIZE); 
    returnMessage = malloc(MAX_MESSAGE_SIZE); 
    if((server_sockfd = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0)) == -1) {
        perror("Error creating server socket"); exit(1); }
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if(bind(server_sockfd, (struct sockaddr *)&local, len) == -1) { perror("binding"); exit(1); }
    if (listen(server_sockfd, 5) == -1) { perror("listen"); exit(1); }
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
    signal(SIGPIPE, SIG_IGN);
    signal(SIGTERM, stop_server);
    SetupSocket();
    OpenFramebuffer();
    EnableGraphicsMode();
    ClearScreen();
    SaveUnderCursor();
    kbfd = OpenKeyboard();
    msfd = OpenMouse();
    pfds[0].fd = kbfd; pfds[0].events = POLLIN;
    pfds[1].fd = msfd; pfds[1].events = POLLIN;
    mouseWentDown = 0;
    mouseWentUp = 0;
    keyWentDown = 0;
    keyWentUp = 0;
    mouseMoved = 0;
    while (1) {
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
                                keyThatWentDown = evt->code;
                                if (evt->code == 42 || evt->code == 54) { shiftDown = 1; }
                                if (evt->code == 29 || evt->code == 97) { ctrlDown = 1; }
                                for (i = 0; i < NUM_KEYS_CHECKED; i++) { prevKeysDown[i] = keysDown[i]; }
                                keysDown[evt->code] = 1;
                            } else if (evt->value == 0) {
                                keyWentUp = 1;
                                keyThatWentUp = evt->code;
                                for (i = 0; i < NUM_KEYS_CHECKED; i++) { prevKeysDown[i] = keysDown[i]; }
                                keysDown[evt->code] = 0;
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
                    if (leftBtn) { mouseDownAtX = mouseX; mouseDownAtY = mouseY; mouseWentDown = 1; mouseIsDown = 1; }
                    else { mouseUpAtX = mouseX; mouseUpAtY = mouseY; mouseWentUp = 1; mouseIsDown = 0; }
                }
                old_leftBtn = leftBtn;
                old_rightBtn = rightBtn;
                old_midBtn = midBtn;
            }
        }
        int socketReadRes = ReadFromSocket();
        if (socketReadRes) {
            HandleMessage();
            send(client_sockfd, totalMessage, totalMessageIdx, 0);
            close(client_sockfd);
        }
        usleep(3000);
    }
    Cleanup();
    return 0;
}
