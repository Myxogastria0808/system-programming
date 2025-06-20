#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// file descriptor 0 is stdin
// file descriptor 1 is stdout
// file descriptor 2 is stderr

// int dup(int oldfd);
// dup returns the lowest-numbered unused file descriptor,
// which refers to the same open file description as oldfd.

// int dup2(int oldfd, int newfd);
// dup2 duplicates oldfd to newfd, closing newfd first if necessary.

int main(int argc, char *argv[]) {
    int read_file_descriptor, write_file_descriptor;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s file_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // open argv[1] file and get the file descriptor
    read_file_descriptor = open(argv[1], O_RDONLY);
    if (read_file_descriptor < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // open argv[2] file and get the file descriptor
    write_file_descriptor = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (write_file_descriptor < 0) {
        perror("open");
        close(read_file_descriptor);
        exit(EXIT_FAILURE);
    }

    // At this point, the file descriptors are likely:
    // 0 ... stdin (still the terminal)
    // 1 ... stdout (still the terminal)
    // 2 ... stderr
    // N (e.g., 3) ... read_file_descriptor
    // N+1 (e.g., 4) ... write_file_descriptor

    // switch stdin to read_file_descriptor
    if (dup2(read_file_descriptor, 0) < 0) {
        perror("dup2");
        close(read_file_descriptor);
        close(write_file_descriptor);
        exit(EXIT_FAILURE);
    }
    // close read_file_descriptor descriptor
    close(read_file_descriptor);

    // switch stdout to write_file_descriptor
    if (dup2(write_file_descriptor, 1) < 0) {
        perror("dup2");
        close(write_file_descriptor);
        exit(EXIT_FAILURE);
    }
    // close write_file_descriptor descriptor
    close(write_file_descriptor);

    // After dup2:
    // 0 ... stdin (now refers to the input file)
    // 1 ... stdout (now refers to the output file)
    // 2 ... stderr (unchanged)

    // execute the wc command
    // input ... stdin (read_file_descriptor)
    // output ... stdout (write_file_descriptor)
    execlp("wc", "wc", NULL);

    return EXIT_FAILURE;
}