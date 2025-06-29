#include <stdio.h>

// キー入力があった場合 ... その値
// EOFが入力された場合 ... -1
// それ以外 ... -3

int main(void) {
    int c = 0;
    signed int flag = 0;
    while (c != EOF) {
        c = getchar();
        if (feof(stdin)) {
            // end signal
            flag = -1;

            printf("end input\n");
        } else if (ferror(stdin)) {
            // error signal
            flag = -3;

            printf("error input\n");
        } else {
            // normal input
            flag = c;

            // debug
            putchar(c);
        }
        printf("\nflag = %d\n", flag);
    }

    return 0;
}