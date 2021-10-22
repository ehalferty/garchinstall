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
#include "keycode_names.h"
#include "cursor.h"
#include "font.h"
#include "arch_logo.h"
#include "close_box_img.h"

#define MOD_LINGER_NANOS 100000000 // How many nanoseconds modifier keys remain down after the user lifts them
#define CURSOR_SIZE 24
#define NUM_KEYS_CHECKED 1024
#define NUM_STEPS 5

uint32_t GetFBOffset(uint32_t x, uint32_t y);
void DrawPixel(uint32_t x2, uint32_t y2, uint8_t r, uint8_t g, uint8_t b);
void DrawPixel32U(uint32_t x2, uint32_t y2, uint32_t c);
void DrawText(uint32_t x, uint32_t y, char *str);
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
void Cleanup();
void DoPage();
int main(int argc, char *argv[]);
