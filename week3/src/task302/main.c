#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define FILE_SIZE 1010000  // 1010000 bytes
#define DUMMY_CHAR '0'

int gen_file(char *argv[]) {
    FILE *file;
    // create src
    file = fopen(argv[1], "w");
    if (file == NULL) {
        fprintf(stderr, "fopen: file: ");
        fclose(file);
        exit(1);
    }
    // write 101000 bytes of '0' to src
    for (int i = 1; i < FILE_SIZE + 1; i++) {
        if (i % 100 == 0) {
            fputc(DUMMY_CHAR, file);
            // indent per 100 characters
            fputc('\n', file);
        } else {
            fputc(DUMMY_CHAR, file);
        }
    }
    // close file
    fclose(file);

    return 0;
}

int fgetc_fputc(char *argv[]) {
    int c;
    FILE *fps, *fpd;

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

int fgets_fputs(char *argv[], int buffer_size) {
    char buffer[buffer_size];
    FILE *fps, *fpd;

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

    while (fgets(buffer, buffer_size, fps) != NULL) {
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

int fread_fwrite(char *argv[], int buffer_size) {
    char buffer[buffer_size];
    FILE *fps, *fpd;

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
        n = fread(buffer, sizeof(char), buffer_size, fps);
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

int read_write(char *argv[], int buffer_size) {
    char *str[buffer_size];
    int fps, fpd;
    int count;

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

    while ((count = read(fps, &str, buffer_size)) > 0) {
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

int main(int argc, char *argv[]) {
    struct timeval start_time;
    struct timeval end_time;
    float elapsed_time;

    // error handling for command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s src_file dst_file\n", argv[0]);
        exit(1);
    }

    // generate file
    gen_file(argv);

    //* fgetc and fputc *//
    gettimeofday(&start_time, NULL);
    // main process
    fgetc_fputc(argv);

    gettimeofday(&end_time, NULL);
    // show result
    elapsed_time = end_time.tv_sec - start_time.tv_sec +
                   ((end_time.tv_usec - start_time.tv_usec) / 1000000.0);
    printf("- fgetc and fputc\n");
    printf("Elapsed time: %f seconds\n", elapsed_time);

    // set 3 buffer sizes
    int buf_size[] = {100, 10000, 1010000};
    for (int i = 0; i < 3; i++) {
        printf("---Buffer size: %7d bytes---\n", buf_size[i]);
        //* fgets and fputs *//
        gettimeofday(&start_time, NULL);
        // main process
        fgets_fputs(argv, buf_size[i]);

        gettimeofday(&end_time, NULL);
        // show result
        elapsed_time = end_time.tv_sec - start_time.tv_sec +
                       ((end_time.tv_usec - start_time.tv_usec) / 1000000.0);
        printf("- fgets and fputs\n");
        printf("Buffer size: %d bytes\n", buf_size[i]);
        printf("Elapsed time: %f seconds\n", elapsed_time);

        //* fread and fwrite *//
        gettimeofday(&start_time, NULL);
        // main process
        fread_fwrite(argv, buf_size[i]);

        gettimeofday(&end_time, NULL);
        // show result
        elapsed_time = end_time.tv_sec - start_time.tv_sec +
                       ((end_time.tv_usec - start_time.tv_usec) / 1000000.0);
        printf("- fread and fwrite\n");
        printf("Buffer size: %d bytes\n", buf_size[i]);
        printf("Elapsed time: %f seconds\n", elapsed_time);

        //* read and write *//
        gettimeofday(&start_time, NULL);
        // main process
        read_write(argv, buf_size[i]);

        gettimeofday(&end_time, NULL);
        // show result
        elapsed_time = end_time.tv_sec - start_time.tv_sec +
                       ((end_time.tv_usec - start_time.tv_usec) / 1000000.0);
        printf("- read and write\n");
        printf("Buffer size: %d bytes\n", buf_size[i]);
        printf("Elapsed time: %f seconds\n", elapsed_time);
        printf("--------------------------------\n");
    }

    return 0;
}
