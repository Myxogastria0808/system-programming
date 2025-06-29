#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1024 * 1024  // 1MB

int main(int argc, char *argv[]) {
    char buffer[MAX_LEN];
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

    while (fgets(buffer, MAX_LEN, fps) != NULL) {
        fputs(buffer, fpd);
        if (ferror(fpd)) {
            perror("fputs");
            fclose(fpd);
            fclose(fps);
            exit(1);
        }
    }
    if (ferror(fps)) {
        perror("fgets");
        fclose(fpd);
        fclose(fps);
        exit(1);
    }

    fclose(fpd);
    fclose(fps);

    return 0;
}