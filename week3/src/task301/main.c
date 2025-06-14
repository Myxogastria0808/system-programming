#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define FILE_SIZE 65536  // 64KB
#define DUMMY_CHAR '0'

int gen_file() {
    FILE *file;
    // create src
    file = fopen("src", "w");
    if (file == NULL) {
        fprintf(stderr, "fopen: file: ");
        fclose(file);
        exit(1);
    }
    // write 65536 bytes of '0' to src
    for (int i = 0; i < FILE_SIZE; i++) {
        fputc(DUMMY_CHAR, file);
    }
    // close file
    fclose(file);

    return 0;
}

int copy_char() {
    char c;
    int fps, fpd;
    int count;
    fps = open("src", O_RDONLY);
    if (fps < 0) {
        perror("open: src");
        exit(1);
    }
    fpd = open("dst", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fpd < 0) {
        perror("open: dst");
        close(fps);
        exit(EXIT_FAILURE);
    }
    while ((count = read(fps, &c, 1)) > 0) {
        if (write(fpd, &c, count) < 0) {
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
        exit(EXIT_FAILURE);
    }
    close(fpd);
    close(fps);

    return 0;
}

int is_same_checker() {
    FILE *src, *dst;
    int src_char, dst_char;

    src = fopen("src", "r");
    if (src == NULL) {
        perror("fopen: src");
        return 1;
    }

    dst = fopen("dst", "r");
    if (dst == NULL) {
        perror("fopen: dst");
        fclose(src);
        return 1;
    }

    while ((src_char = fgetc(src)) != EOF && (dst_char = fgetc(dst)) != EOF) {
        if (src_char != dst_char) {
            fclose(src);
            fclose(dst);
            exit(EXIT_FAILURE);
        }
    }

    fclose(src);
    fclose(dst);

    return 0;
}

int copy_n(int n) {
    char *str[n];
    int fps, fpd;
    int count;

    fps = open("src", O_RDONLY);
    if (fps < 0) {
        perror("open: src");
        exit(EXIT_FAILURE);
    }

    fpd = open("dst", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fpd < 0) {
        perror("open: dst");
        close(fps);
        exit(EXIT_FAILURE);
    }

    while ((count = read(fps, &str, n)) > 0) {
        if (write(fpd, &str, count) < 0) {
            perror("write");
            close(fpd);
            close(fps);
            fprintf(stderr, "Check is same: Failed\n");
            exit(EXIT_FAILURE);
        }
    }

    if (count < 0) {
        perror("read");
        close(fpd);
        close(fps);
        exit(EXIT_FAILURE);
    }

    close(fpd);
    close(fps);

    fprintf(stdout, "Check is same: OK\n");

    return 0;
}

int main() {
    struct timeval start_time;
    struct timeval end_time;
    float elapsed_time;

    //* generate src *//
    gen_file();

    //* main process of per 1 char *//
    // Start Time
    gettimeofday(&start_time, NULL);

    // Main Process
    copy_char();

    // End Time
    gettimeofday(&end_time, NULL);
    // Show Result
    elapsed_time = end_time.tv_sec - start_time.tv_sec +
                   ((end_time.tv_usec - start_time.tv_usec) / 1000000.0);
    printf("Per 1 character\n");
    printf("Elapsed time: %f seconds\n", elapsed_time);
    // Check Is Same
    is_same_checker();

    //* main process of per BUFSIZ *//
    // Start Time
    gettimeofday(&start_time, NULL);

    // Main Process
    copy_n(BUFSIZ);

    // End Time
    gettimeofday(&end_time, NULL);
    // Show Result
    elapsed_time = end_time.tv_sec - start_time.tv_sec +
                   ((end_time.tv_usec - start_time.tv_usec) / 1000000.0);
    printf("Per 1 BUFSIZ (%d)\n", BUFSIZ);
    printf("Elapsed time: %f seconds\n", elapsed_time);
    // Check Is Same
    is_same_checker();

    //* main process of per N character *//
    int n;
    for (int i = 1; i <= 100; i++) {
        // Set N
        n = i * 1024;
        // Start Time
        gettimeofday(&start_time, NULL);

        // Main Process
        copy_n(n);

        // End Time
        gettimeofday(&end_time, NULL);
        // Show Result
        elapsed_time = end_time.tv_sec - start_time.tv_sec +
                       ((end_time.tv_usec - start_time.tv_usec) / 1000000.0);
        if (i % 10 == 0) {
            printf("Per %d character\n", n);
            printf("Elapsed time: %f seconds\n", elapsed_time);
        }
        // Check Is Same
        is_same_checker();
    }

    return 0;
}
