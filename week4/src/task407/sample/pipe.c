#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>

int pipe_fd[2];

void do_child(void) {
    char *p = "Hello, dad or mam!\n";

    // the outputs independently of the pipe
    printf("This is child.\n");

    // close exit of a child process pipe
    close(pipe_fd[0]);

    // write a string to the pipe
    while (*p != '\0') {
        if (write(pipe_fd[1], p, 1) < 0) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        p++;
    }
}

void do_parent(void) {
    char c;
    int count, status;

    // the outputs independently of the pipe
    printf("This is parent.\n");

    // close entry of a parent process pipe
    close(pipe_fd[1]);

    // ↓pipe has I/O blocking function
    // wait for the child process to finish writing message
    while ((count = read(pipe_fd[0], &c, 1)) > 0) {
        putchar(c);
    }

    if (count < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // if the child process has finished writing,
    // close the exit of the pipe and collect it
    if (wait(&status) < 0) {
        perror("wait");
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    int child;

    // create a pipe
    // int pipe(int fildes[2]);
    // fildes[0] ... exit of a pipe
    // fildes[1] ... entry of a pipe
    if (pipe(pipe_fd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // create a child process
    if ((child = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // run both processes in this point

    // fork returns 0 → the child process
    // dork returns the child's PID → the parent process
    // There is no guarantee that either the child or
    // the parent process will be executed first
    if (child) {
        // parent process
        do_parent();
    } else {
        // child process
        do_child();
    }

    return EXIT_SUCCESS;
}

// the prpgram runs as follows:
// parent_process
//   |
//  fork ---------------------> child_process
//   |                                |
//   |   (run parallel)               |
//   |                                |
//   | <- lock read pipe              |
//   |     ↑                          |
//   |    pipe I/O blocking           |
//   |    pipe_fd[0] is empty → BLOCK |
//   |                                | <- write to pipe
//   | <- unlock read pipe            |
//   |                                |
//   | <- read from pipe              |
//   |                                |
//   | <----------------------- close_child_process (wait function)
//   ↓
//  exit
