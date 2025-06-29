#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "sample.txt"
#define FILE_SIZE 65536
#define DUMMY_CHAR '0'

int main() {
    FILE *file;
    // create sample.txt
    file = fopen("sample.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "fopen: file: ");
        fclose(file);
        exit(1);
    }
    // write 65536 bytes of '0' to sample.txt
    for (int i = 0; i < FILE_SIZE; i++) {
        fputc(DUMMY_CHAR, file);
    }
    // close file
    fclose(file);

    return 0;
}
