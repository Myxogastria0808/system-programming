#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

volatile sig_atomic_t alrm_count = 10;

void alrm(int signum) { alrm_count--; }

int main(void) {
    struct sigaction sa_alarm;
    struct itimerval itimer;

    memset(&sa_alarm, 0, sizeof(sa_alarm));
    sa_alarm.sa_handler = alrm;
    sa_alarm.sa_flags = SA_RESTART;

    if (sigaction(SIGALRM, &sa_alarm, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    itimer.it_value.tv_sec = itimer.it_interval.tv_sec = 1;
    itimer.it_value.tv_usec = itimer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &itimer, NULL) < 0) {
        perror("setitimer");
        exit(1);
    }

    while (alrm_count) {
        pause();
        printf("%d: %ld\n", alrm_count, time(NULL));
    }

    itimer.it_value.tv_sec = itimer.it_interval.tv_sec = 0;
    itimer.it_value.tv_usec = itimer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &itimer, NULL) < 0) {
        perror("setitimer");
        exit(1);
    }

    return 0;
}
