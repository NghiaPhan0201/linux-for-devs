#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int seconds = 0;

void sigalrm_handler(int sig) {
    seconds++;
    printf("Timer: %d seconds\n", seconds);
    
    if (seconds >= 10) {
        printf("Timer reached 10 seconds, exiting...\n");
        _exit(0);
    }
    alarm(1);
}

int main() {
    signal(SIGALRM, sigalrm_handler);
    
    printf("Starting timer...\n");
    alarm(1);
    
    while (1) {
        sleep(1);
    }
    return 0;
}