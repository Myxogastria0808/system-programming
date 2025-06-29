#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

volatile sig_atomic_t result = 0;

void signal_handler(int signum) {
    if (signum == SIGALRM) {
        // get SIGALRM signal
        result = -2;
    }
    if (signum == SIGINT) {
        // get SIGINT signal (Ctrl+C)
        result = -3;
    }
}

signed int mygetchar(time_t time) {
    struct sigaction sa_alarm;
    struct itimerval itimer;

    // initialize the alarm signal handler
    memset(&sa_alarm, 0, sizeof(sa_alarm));
    sa_alarm.sa_handler = signal_handler;
    sa_alarm.sa_flags = 0;

    // set the signal handler for SIGALRM
    if (sigaction(SIGALRM, &sa_alarm, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    // set the signal handler for SIGINT
    if (sigaction(SIGINT, &sa_alarm, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    // initialize the timer
    itimer.it_value.tv_sec = itimer.it_interval.tv_sec = time;
    itimer.it_value.tv_usec = itimer.it_interval.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &itimer, NULL) < 0) {
        perror("setitimer");
        exit(1);
    }

    // wait for input or timeout
    int c = getchar();

    // get EOF (Ctrl+D) signal
    if (feof(stdin)) {
        // input EOF
        result = -1;
    }

    // check result has success flag
    if (result == 0) {
        // normal input
        result = c;
    }

    // reset the timer
    itimer.it_value.tv_sec = itimer.it_interval.tv_sec = 0;
    itimer.it_value.tv_usec = itimer.it_interval.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &itimer, NULL) < 0) {
        perror("setitimer");
        exit(1);
    }

    return result;
}

int main(int argc, char *argv[]) {
    // argument validation
    if (argc != 2) {
        perror("argc");
        exit(EXIT_FAILURE);
    }

    // convert argument to time_t
    time_t time = atoi(argv[1]);
    if (time <= 0) {
        perror("time");
        exit(EXIT_FAILURE);
    }

    // execute mygetchar function
    signed int output = mygetchar(time);

    // show output
    printf("---- Output ----\n");
    if (output >= 0) {
        printf("Input received: %c\n", c);
        printf("%c\n", output);
    } else if (output == -1) {
        printf("EOF (Ctrl+D) received\n");
        printf("%d\n", output);
    } else if (output == -2) {
        printf("SIGALRM received (Timeout occurred)\n");
        printf("%d\n", output);
    } else if (output == -3) {
        printf("SIGINT (Ctrl+C) received\n");
        printf("%d\n", output);
    } else {
        printf("Unknown output: %d\n", output);
    }

    return 0;
}