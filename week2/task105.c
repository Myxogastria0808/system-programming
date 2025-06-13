#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

size_t my_strlcpy(char *dst, const char *src, size_t size) {
    // get src length
    size_t src_len = strlen(src);
    // copy up to size - 1 characters from src to dst
    size_t actual_size = size - 1;
    for (size_t i = 0; i < actual_size; i++) {
        dst[i] = src[i];
    }
    // set null the end of the destination string
    dst[actual_size] = '\0';

    return src_len;
}

char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *new_str = malloc(len + 1);
    //  validate about creating malloc
    if (new_str == NULL) {
        return NULL;
    }
    // copy
    for (size_t i = 0; i <= len; i++) {
        new_str[i] = s[i];
        // set null the end of the new string
        if (i == len) {
            new_str[i] = '\0';
        }
    }
    return new_str;
}

#define BUF_SIZE 5000000
#define LOOP_SIZE 1000

int main(void) {
    //* Pre Process *//
    // 100_000
    char buffer[BUF_SIZE];
    for (int i = 0; i < BUF_SIZE; i++) {
        if (i == (BUF_SIZE - 1)) {
            buffer[i] = '\0';
        } else {
            buffer[i] = 'a';
        }
    }
    char s1[BUF_SIZE];
    for (int i = 0; i < BUF_SIZE; i++) {
        if (i == (BUF_SIZE - 1)) {
            s1[i] = '\0';
        } else {
            s1[i] = 'b';
        }
    }

    //* check is same process *//
    // check strlcpy and my_strlcpy
    char test_buffer1[15];
    char test_buffer2[17];
    char *test_s1 = "Hello, World!";
    char *test_s2 = "Hello, TSUKUBA!";
    strlcpy(test_buffer1, test_s1, 15);
    my_strlcpy(test_buffer2, test_s2, 17);
    if (strcmp(test_buffer1, test_s1) != 0) {
        fprintf(stderr, "strlcpy and my_strlcpy output same result\n");
        exit(1);
    }
    if (strcmp(test_buffer2, test_s2) != 0) {
        fprintf(stderr, "strlcpy and my_strlcpy output same result\n");
        exit(1);
    }
    printf("strlcpy and my_strlcpy output same result\n");

    // check strdup and my_strdup
    char *test_buffer3 = strdup(test_s1);
    if (test_buffer3 == NULL) {
        fprintf(stderr, "malloc failed");
        exit(1);
    }
    char *test_buffer4 = my_strdup(test_s2);
    if (test_buffer4 == NULL) {
        fprintf(stderr, "malloc failed");
        exit(1);
    }
    if (strcmp(test_buffer3, test_s1) != 0) {
        fprintf(stderr, "strdup and my_strdup output same result\n");
        exit(1);
    }
    if (strcmp(test_buffer4, test_s2) != 0) {
        fprintf(stderr, "strdup and my_strdup output same result\n");
        exit(1);
    }
    printf("strldup and my_strdup output same result\n");
    free(test_buffer3);
    free(test_buffer4);

    //* main process of strlcpy *//
    clock_t start_strlcpy_time, end_strlcpy_time;
    // start time
    start_strlcpy_time = clock();
    // main process of strlcpy
    for (int i = 0; i < LOOP_SIZE; i++) {
        // copy s1 to buffer
        strlcpy(buffer, s1, BUF_SIZE);
    }
    // end time
    end_strlcpy_time = clock();

    // result
    clock_t elapsed_strlcpy_time = end_strlcpy_time - start_strlcpy_time;
    fprintf(stdout, "strlcpy time: %f\n",
            (double)elapsed_strlcpy_time / CLOCKS_PER_SEC);
    fprintf(stdout, "average of strlcpy time: %f\n",
            (double)elapsed_strlcpy_time / CLOCKS_PER_SEC / LOOP_SIZE);

    //* main process of my_strlcpy *//
    clock_t start_my_strlcpy_time, end_my_strlcpy_time;
    // start time
    start_my_strlcpy_time = clock();
    // main process of my_strlcpy
    for (int i = 0; i < LOOP_SIZE; i++) {
        // copy s1 to buffer
        my_strlcpy(buffer, s1, BUF_SIZE);
    }
    // end time
    end_my_strlcpy_time = clock();

    // result
    clock_t elapsed_my_strlcpy_time =
        end_my_strlcpy_time - start_my_strlcpy_time;
    fprintf(stdout, "my_strlcpy time: %f\n",
            (double)elapsed_my_strlcpy_time / CLOCKS_PER_SEC);
    fprintf(stdout, "average of my_strlcpy time: %f\n",
            (double)elapsed_my_strlcpy_time / CLOCKS_PER_SEC / LOOP_SIZE);

    //* main process of strdup *//
    clock_t start_strdup_time, end_strdup_time;
    // start time
    start_strdup_time = clock();
    // main process of strdup
    for (int i = 0; i < LOOP_SIZE; i++) {
        char *s2 = strdup(s1);
        if (s2 == NULL) {
            fprintf(stderr, "malloc failed");
            exit(1);
        }
        free(s2);
    }
    // end time
    end_strdup_time = clock();

    // result
    clock_t elapsed_strdup_time = end_strdup_time - start_strdup_time;
    fprintf(stdout, "strdup time: %f\n",
            (double)elapsed_strdup_time / CLOCKS_PER_SEC);
    fprintf(stdout, "average of strdup time: %f\n",
            (double)elapsed_strdup_time / CLOCKS_PER_SEC / LOOP_SIZE);

    //* main process of my_strdup *//
    clock_t start_my_strdup_time, end_my_strdup_time;
    // start time
    start_my_strdup_time = clock();
    // main process of my_strdup
    for (int i = 0; i < LOOP_SIZE; i++) {
        char *s2 = my_strdup(s1);
        if (s2 == NULL) {
            fprintf(stderr, "malloc failed");
            exit(1);
        }
        free(s2);
    }
    // end time
    end_my_strdup_time = clock();

    // result
    clock_t elapsed_my_strdup_time = end_my_strdup_time - start_my_strdup_time;
    fprintf(stdout, "my_strdup time: %f\n",
            (double)elapsed_my_strdup_time / CLOCKS_PER_SEC);
    fprintf(stdout, "average of my_strdup time: %f\n",
            (double)elapsed_my_strdup_time / CLOCKS_PER_SEC / LOOP_SIZE);

    return 0;
}
