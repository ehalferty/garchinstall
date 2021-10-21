#include "main.h"
int main(int argc, char *argv[]) {
    FILE *gzFile = fopen("garchinstall.tar.gz", "w");
    for (int i = 0; i < GZ_FILE_SIZE; i++) {
        fputc(garchinstall[i], gzFile);
    }
    system("tar -xzf garchinstall.tar.gz");
    return 0;
}
