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
#include <wait.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <linux/kd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/un.h>
#include "keycode_names.h"
#include "cursor.h"
#include "font.h"

#define MOD_LINGER_NANOS 100000000 // How many nanoseconds modifier keys remain down after the user lifts them
#define CURSOR_SIZE 24
#define NUM_KEYS_CHECKED 1024
#define NUM_STEPS 5
#define PID_PATH "/tmp/gui_server.pid"
#define SOCK_PATH "/tmp/gui_server_socket"
#define LOG_PATH "/tmp/gui_server.log"
#define MAX_MESSAGE_SIZE 1024*1024*16 // 16 MB

#define MSG_CLEAR_SCREEN 1
#define MSG_SET_FGCOLOR 2
#define MSG_SET_BGCOLOR 3
#define MSG_DRAW_RECT 4
#define MSG_LOAD_BITMAP 5
#define MSG_DRAW_BITMAP 6
#define MSG_DRAW_TEXT 7
#define MSG_GET_EVENTS 8
#define MSG_GET_KEYS 9

uint32_t GetFBOffset(uint32_t x, uint32_t y);
void DrawPixel(uint32_t x2, uint32_t y2, uint8_t r, uint8_t g, uint8_t b);
void DrawPixel32U(uint32_t x2, uint32_t y2, uint32_t c);
void DrawText(uint32_t x, uint32_t y, char *str);
void DrawRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
uint32_t GetPixel(uint32_t x2, uint32_t y2);
void DrawBitmap(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t *bmp);
void DrawArchLogo(uint32_t x, uint32_t y);
void DrawCloseBox();
void DrawNextButton();
void ClearScreen();
void OpenFramebuffer();
int OpenKeyboard();
int OpenMouse();
void SaveUnderCursor();
void RestoreUnderCursor();
void DrawCursor();
uint32_t MouseDownAndUpWithinRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void ExitNormally();
void ExitWithError(char *msg);
void Cleanup();
uint8_t * LoadBitmap(const char *path);
void FreeBitmap(uint8_t *bmp);
void EnableGraphicsMode();
void SetupSocket();
void stop_server();
int ReadFromSocket();
void HandleMessage();
int main(int argc, char *argv[]);
