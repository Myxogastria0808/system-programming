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

    size_t n;
    while (!feof(fps)) {
        n = fread(buffer, sizeof(char), MAX_LEN, fps);
        if (ferror(fps)) {
            perror("fread");
            fclose(fpd);
            fclose(fps);
            exit(EXIT_FAILURE);
        }
        fwrite(buffer, sizeof(char), n, fpd);
        if (ferror(fpd)) {
            perror("fwrite");
            fclose(fpd);
            fclose(fps);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fpd);
    fclose(fps);

    return 0;
}
