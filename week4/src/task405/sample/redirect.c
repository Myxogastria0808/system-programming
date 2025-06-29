#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// file descriptor 0 is stdin
// file descriptor 1 is stdout
// file descriptor 2 is stderr

// int dup(int oldfd);
// dup func use a file descriptor
// that is smallest unused value in the dup is called.

// int dup2(int oldfd, int newfd);
// dup2 func use a file descriptor that is specified by newfd.

int main(int argc, char *argv[]) {
    int file_fd;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s file_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // open the file specified in the argv[1] argument
    // and get the file descriptor
    // maybe file_fd = 3
    file_fd = open(argv[1], O_RDONLY);
    if (file_fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    // close stdin descriptor
    close(0);

    // dup2 enables me to access argv[1] file from file descriptor 0
    // the proccess is that dup2 replaces the file descriptor 0
    // with the file descriptor file_fd
    if (dup2(file_fd, 0) < 0) {
        perror("dup2");
        close(file_fd);
        exit(EXIT_FAILURE);
    }

    // execute the wc command
    // wc command reads from file descriptor 0
    // and counts the number of lines, words, and characters
    // in the file specified in argv[1] file
    execlp("wc", "wc", NULL);

    return EXIT_FAILURE;
}
