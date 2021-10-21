#include "main.h"
int main(int argc, char *argv[]) {
    FILE *gzFile = fopen("garchinstall.tar.gz", "w");
    for (int i = 0; i < GZ_FILE_SIZE; i++) {
        fputc(garchinstall[i], gzFile);
    }
    fclose(gzFile);
    system("tar -xzf garchinstall.tar.gz");
    char *eargs[3];
    eargs[0] = malloc(128);
    eargs[1] = malloc(128);
    eargs[2] = 0;
    sprintf(eargs[0], "/usr/bin/perl");
    sprintf(eargs[1], "perl/garchinstall.pl");
    execve("/usr/bin/perl", eargs, NULL);
    // system("perl perl/garchinstall.pl");
    return 0;
}
