/*
        file-counter.c -- ファイルに値を保存するカウンタ
        ~yas/syspro/file/file-counter.c
*/

#include <stdio.h>  /* stderr, fopen(), fread(), frwite(), fclose() */
#include <stdlib.h> /* exit(), strtol() */
#include <string.h> /* strcmp() */

int counter_load();
void counter_save(int counter);

#define DATA_FILENAME "file-counter-value.data"
char *comname = "";

void usage() {
    printf("Usage$ %s {get,inc,set newvalue} {args}\n", comname);
    printf("Data file: %s\n", DATA_FILENAME);
    exit(1);
}

int main(int argc, char *argv[]) {
    char *cmd;
    int counter, newvalue;
    comname = argv[0];
    if (argc <= 1) usage();
    cmd = argv[1];
    counter = 0;
    if (strcmp(cmd, "get") == 0) {
        counter = counter_load();
    } else if (strcmp(cmd, "inc") == 0) {
        counter = counter_load();
        counter++;
    } else if (strcmp(cmd, "set") == 0) {
        if (argc != 3) usage();
        newvalue = strtol(argv[2], 0, 10);
        counter = newvalue;
    } else {
        usage();
    }
    printf("%d\n", counter);
    if (strcmp(cmd, "get") != 0) counter_save(counter);
    return 0;
}

void counter_save(int counter) {
    FILE *f;
    f = fopen(DATA_FILENAME, "w");
    if (f == NULL) {
        perror(DATA_FILENAME);
        exit(2);
    }
    if (fwrite(&counter, sizeof(counter), 1, f) != 1) {
        perror("fwrite");
        fclose(f);
        exit(2);
    }
    fclose(f);
}

int counter_load() {
    FILE *f;
    int counter;
    f = fopen(DATA_FILENAME, "r");
    if (f == NULL) {
        return 0;
    }
    if (fread(&counter, sizeof(counter), 1, f) != 1) {
        perror("fread");
        fclose(f);
        exit(2);
    }
    fclose(f);
    return counter;
}