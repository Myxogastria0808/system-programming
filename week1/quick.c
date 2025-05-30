#include <stdio.h>

#define SAMPLE_COUNT 6
int sample[SAMPLE_COUNT] = {8, 12, 3, 15, 7, 4};
int recursive_count = 0;
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

int quick_sort(int a[], int upper, int lower) {
    int pivot, pivot_index, tmp, i, j;

    i = upper;
    j = lower;
    // upperとlowerの中間をpivotとする
    pivot = a[(upper + lower) / 2];
    pivot_index = (upper + lower) / 2;
    // iとjが交差するまで繰り返す
    while (i <= j) {
        // pivotより小さい値を左側に、pivotより大きい値を右側に移動する
        // 左側ではpivotより大きい値が出るまでiを進める
        while ( a[i] < pivot ) {
            i++;
            compare_count++;
        }
        // 右側ではpivotより小さい値が出るまでjを戻す
        while ( a[j] > pivot ) {
            j--;
            compare_count++;
        }
        printf("\t[%d] = %2d >= %2d && [%d] = %2d <= %2d", i, a[i], pivot, j, a[j], pivot);
        if (i <= j) {
            printf(" ... swap!!");
            swap_array(a, i, j);
            i++;
            j--;
            swap_count++;
        } else {
            printf(" ... crossed!! (i > j)");
        }
        printf("\n");
    }
    //* print result area *//
    recursive_count++;
    printf("%d: ", recursive_count);
    print_data(a, SAMPLE_COUNT);
    // lower
    if (a[0] == pivot) {
        printf("lower:\n");
    }
    else {
        printf("lower: ");
        for (int k = 0; k < (i - 1); k++) {
            printf("%2d ", a[k]);
        }
        if (a[i - 1] == pivot) {
            printf("\n");
        } else {
            printf("%2d\n", a[i - 1]);
        }
    }
    // pivot
    printf("pivot: %2d\n", pivot);
    //upper
    if (a[j + 1] == pivot) {
        printf("upper: ");
        for (int k = j + 2; k < (SAMPLE_COUNT - 1); k++) {
            printf("%2d ", a[k]);
        }
        if (a[SAMPLE_COUNT - 1] == pivot) {
            printf("\n");
        } else {
            printf("%2d\n", a[SAMPLE_COUNT - 1]);
        }
    } else {
        printf("upper: ");
        for (int k = j + 1; k < (SAMPLE_COUNT - 1); k++) {
            printf("%2d ", a[k]);
        }
        printf("%2d\n", a[SAMPLE_COUNT - 1]);
    }
    //* print result area *//

    if ( upper < j ) quick_sort(a, upper, j);
    if ( i < lower ) quick_sort(a, i, lower);
}

int quick_sort_wapper(int data[], int count) {
    quick_sort(data, 0, count - 1);
}

int main(void) {
    quick_sort_wapper(sample, SAMPLE_COUNT);
    printf("-----quick sort result-----\n");
    print_data(sample, SAMPLE_COUNT);
    printf("compare times: %d\n", compare_count);
    printf("swap times: %d\n", swap_count);
    return 0;
}
