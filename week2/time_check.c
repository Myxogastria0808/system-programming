#include <stdio.h>
#include <time.h>

int main(void) {
    int i;
    clock_t start_time, end_time;

    // pre_process sample
    for (i = 0; i < 100000; i++) {
        printf("pre_process\n");
    }

    // start check
    start_time = clock();

    //* main process sample *//
    for (i = 0; i < 1000000; i++) {
        printf("main_process\n");
    }

    // end check
    end_time = clock();

    // result
    clock_t elapsed_time = end_time - start_time;
    printf("all CPU time: %ld\n", end_time);
    fprintf(stdout, "Result CPU time: %ld, Result Sec time: %f\n", elapsed_time,
            (double)elapsed_time / CLOCKS_PER_SEC);

    return 0;
}