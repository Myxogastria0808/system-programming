#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void char_converter(char c) {
    if (isblank(c)) {
        // convert blank to period
        putchar('.');
    } else if (islower(c)) {
        // convert lower case to upper case
        putchar(toupper(c));
    } else {
        // other characters remain unchanged
        putchar(c);
    }
}

int main(int argc, char const *argv[]) {
    int c;
    // TSUKUBA counter
    int tsukuba_cnt = 0;
    // TSUKUBA buffer
    char *tsukuba = "TSUKUBA";

    // if command line arguments are given, print usage message
    if (argc > 1) {
        fprintf(stderr,
                "This program cannot t_buf[TSUKUBA_LEN];ake command line "
                "arguments.\n");
        exit(1);
    }

    while ((c = getchar()) != EOF) {
        // check for "TSUKUBA" in the input
        if (c == 84 && tsukuba_cnt == 0) {  // ASCII code for 'T'
            tsukuba_cnt++;
        } else if (c == 83 && tsukuba_cnt == 1) {  // ASCII code for 'S'
            tsukuba_cnt++;
        } else if (c == 85 && tsukuba_cnt == 2) {  // ASCII code for 'U'
            tsukuba_cnt++;
        } else if (c == 75 && tsukuba_cnt == 3) {  // ASCII code for 'K'
            tsukuba_cnt++;
        } else if (c == 85 && tsukuba_cnt == 4) {  // ASCII code for 'U'
            tsukuba_cnt++;
        } else if (c == 66 && tsukuba_cnt == 5) {  // ASCII code for 'B'
            tsukuba_cnt++;
        } else if (c == 65 && tsukuba_cnt == 6) {  // ASCII code for 'A'
            // reset tsukuba_cnt
            tsukuba_cnt = 0;
            fprintf(stderr, "I found TSUKUBA!\n");
        } else if (tsukuba_cnt > 0) {
            // if not complete "TSUKUBA", show string
            printf("flag is not complete\n");
            if (tsukuba_cnt < 7) {
                for (int i = 0; i < tsukuba_cnt; i++) {
                    putchar(tsukuba[i]);
                }
            }

            // process of next character
            if (c == 84) {  // ASCII code for 'T'
                // if next character is 'T', count 1
                tsukuba_cnt = 1;
            } else {
                char_converter(c);
                // reset tsukuba_cnt
                tsukuba_cnt = 0;
            }
        } else {
            // other characters
            char_converter(c);
        }
    }

    return 0;
}