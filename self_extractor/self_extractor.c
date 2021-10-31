#include "self_extractor.h"
int main(int argc, char *argv[]) {
    FILE *gzFile = fopen("bundle.tar.gz", "w");
    for (int i = 0; i < GZ_FILE_SIZE; i++) {
        fputc(bundle[i], gzFile);
    }
    fclose(gzFile);
    system("tar -xzf bundle.tar.gz");
    char *eargs[3];
    eargs[0] = malloc(128);
    eargs[1] = malloc(128);
    eargs[2] = 0;
    sprintf(eargs[0], "/usr/bin/perl");
    sprintf(eargs[1], "bundle/installer/00_init.pl");
    execve("/usr/bin/perl", eargs, NULL);
    return 0;
}
