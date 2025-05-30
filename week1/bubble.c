#include <stdio.h>

#define SAMPLE_COUNT 6
int sample[SAMPLE_COUNT] = {8, 12, 3, 15, 7, 4};
int compare_count = 0;
int swap_count = 0;

void print_data(int a[], int count) {
    int i;
    for (i = 0; i < count; i++) {
        printf("%2d ", a[i]);
    }
    printf("\n");
}

void swap_array(int a[], int i, int j) {
    int tmp;
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void bubble_sort(int data[], int count) {
    int i, j;
    int n = count - 1;
    for (i = 0; i < n; i++) {
        printf("%d: ", i);
        print_data(data, count);
        for (j = 0; j < n - i; j++) {
            compare_count++;
            printf("\t[%d]=%d > [%d]=%d", j, data[j], j + 1, data[j + 1]);
            if (data[j] > data[j + 1]) {
                printf(" ... swap!!");
                swap_array(data, j, j + 1);
                swap_count++;
            }
            printf("\n");
        }
    }
}

int main(void) {
    bubble_sort(sample, SAMPLE_COUNT);
    printf("-----bubble sort result-----\n");
    print_data(sample, SAMPLE_COUNT);
    printf("compare times: %d\n", compare_count);
    printf("swap times: %d\n", swap_count);
    return 0;
}
