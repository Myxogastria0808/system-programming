#include <fcntl.h>
#include <stdio.h>

#define MAX_LEN 1024 * 1024  // 1MB

int main(int argc, char *argv[]) {
    char *str[MAX_LEN];
    int fps, fpd;
    int count;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s src_file dst_file\n", argv[0]);
        exit(1);
    }

    fps = open(argv[1], O_RDONLY);
    if (fps < 0) {
        perror(argv[1]);
        exit(1);
    }

    fpd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fpd < 0) {
        perror(argv[2]);
        close(fps);
        exit(1);
    }

    while ((count = read(fps, &str, 1)) > 0) {
        if (write(fpd, &str, count) < 0) {
            perror("write");
            close(fpd);
            close(fps);
            exit(1);
        }
    }
    if (count < 0) {
        perror("read");
        close(fpd);
        close(fps);
        exit(1);
    }

    close(fpd);
    close(fps);

    return 0;
}
