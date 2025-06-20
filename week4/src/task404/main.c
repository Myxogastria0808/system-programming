#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// parent process
//  ↓
// fork -------------→|
//  ↓                 ↓
// wait              execl
//  |                 |
// wait for child     |
// process complete   |
//   |                ↓
//   |               exit
//   ↓                ↓
// restart execute ←---
//   ↓

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
}

int main() {
    int status;

    const char *command = "echo Hello, World!";
    const char *command2 =
        "echo Hello, World! > output.txt | sed -e \"s/World/Universe/g\" "
        "output.txt ";
    const char *command3 = "cat output.txt";

    // Call mysystem to execute some commands
    printf("Executing command: %s\n", command);
    status = mysystem(command);
    if (status < 0) {
        perror("mysystem");
        return EXIT_FAILURE;
    }

    printf("Executing command2: %s\n", command2);
    status = mysystem(command2);
    if (status < 0) {
        perror("mysystem");
        return EXIT_FAILURE;
    }

    printf("Executing command3: %s\n", command3);
    status = mysystem(command3);
    if (status < 0) {
        perror("mysystem");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}