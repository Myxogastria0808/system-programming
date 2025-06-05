#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define TSUKUBA_LEN 7

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
    char tsukuba_buf[TSUKUBA_LEN];

    // if command line arguments are given, print usage message
    if (argc > 1) {
        fprintf(stderr, "This program cannot take command line arguments.\n");
        exit(1);
    }

    while ((c = getchar()) != EOF) {
        // check for "TSUKUBA" in the input
        if (c == 84) {  // ASCII code for 'T'
            tsukuba_cnt++;
            tsukuba_buf[0] = c;  // store 'T' in buffer
            tsukuba_buf[1] = '\0';
        } else if (c == 83 && tsukuba_cnt == 1) {  // ASCII code for 'S'
            tsukuba_cnt++;
            tsukuba_buf[1] = c;  // store 'S' in buffer
            tsukuba_buf[2] = '\0';
        } else if (c == 85 && tsukuba_cnt == 2) {  // ASCII code for 'U'
            tsukuba_cnt++;
            tsukuba_buf[2] = c;  // store 'U' in buffer
            tsukuba_buf[3] = '\0';
        } else if (c == 75 && tsukuba_cnt == 3) {  // ASCII code for 'K'
            tsukuba_cnt++;
            tsukuba_buf[3] = c;  // store 'K' in buffer
            tsukuba_buf[4] = '\0';
        } else if (c == 85 && tsukuba_cnt == 4) {  // ASCII code for 'U'
            tsukuba_cnt++;
            tsukuba_buf[4] = c;  // store 'U' in buffer
            tsukuba_buf[5] = '\0';
        } else if (c == 66 && tsukuba_cnt == 5) {  // ASCII code for 'B'
            tsukuba_cnt++;
            tsukuba_buf[5] = c;  // store 'B' in buffer
            tsukuba_buf[6] = '\0';
        } else if (c == 65 && tsukuba_cnt == 6) {  // ASCII code for 'A'
            // reset tsukuba_cnt
            tsukuba_cnt = 0;
            // initialize buffer
            tsukuba_buf[0] = '\0';
            fprintf(stderr, "I found TSUKUBA!\n");
        } else if (tsukuba_cnt > 0) {
            // if not complete "TSUKUBA", show buffer string
            if (tsukuba_cnt < 7) printf("%s", tsukuba_buf);

            // reset tsukuba_cnt if not matching
            tsukuba_cnt = 0;

            // other characters
            char_converter(c);
        } else {
            // other characters
            char_converter(c);
        }
    }

    return 0;
}