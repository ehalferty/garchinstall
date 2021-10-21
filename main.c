#include "main.h"
int main(int argc, char *argv[]) {
    FILE *gzFile = fopen("garchinstall.tar.gz", "w");
    for (int i = 0; i < GZ_FILE_SIZE; i++) {
        fputc(garchinstall[i], gzFile);
    }
    fclose(gzFile);
    system("tar -xzf garchinstall.tar.gz");
    system("perl garchinstall/garchinstall.pl");
    return 0;
}
