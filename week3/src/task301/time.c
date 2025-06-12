#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval start_time;
    struct timeval end_time;
    float elapsed_time;

    gettimeofday(&start_time, NULL);

    // Main Process
    for (int i = 0; i < 1000000; i++) {
        printf("Main Process %d\n", i);
    }

    gettimeofday(&end_time, NULL);

    // Show Result
    printf("Start Time: %ld.%06lu\n", start_time.tv_sec, start_time.tv_usec);
    printf("End Time: %ld.%06lu\n", end_time.tv_sec, end_time.tv_usec);
    elapsed_time = end_time.tv_sec - start_time.tv_sec +
                   ((end_time.tv_usec - start_time.tv_usec) / 1000000.0);
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}