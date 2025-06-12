#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int c;
    FILE *fps, *fpd;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s src_file dst_file\n", argv[0]);
        exit(1);
    }

    fps = fopen(argv[1], "r");
    if (fps == NULL) {
        perror(argv[1]);
        exit(1);
    }

    fpd = fopen(argv[2], "w");
    if (fpd == NULL) {
        perror(argv[2]);
        fclose(fps);
        exit(1);
    }

    while ((c = fgetc(fps)) != EOF) {
        fputc(c, fpd);
    }

    fclose(fpd);
    fclose(fps);

    return 0;
}