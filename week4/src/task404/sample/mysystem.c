// 親プロセス
//   ↓
//  fork---------------
//   ↓                ↓
//  wait           execve
//   |                |
// wait for child     |
//   |                ↓
//   |               exit
//   ↓                ↓
// 実行再開 ←-----------
//   ↓

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int mysystem_child(const char *command) {
    return execl("/bin/sh", "sh", "-c", command, NULL);
}

int mysystem(const char *command) {
    // NULL check
    if (command == NULL) {
        return EXIT_FAILURE;
    }

    int child, status;

    // create a child process
    if ((child = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child == 0) {
        // run the command using execl
        return mysystem_child(command);
    } else {
        // wait for the child process to finish
        if (wait(&status) < 0) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
};