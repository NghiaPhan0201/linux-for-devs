#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int sigint_count = 0;

void sigint_handler(int sig) {

    printf("SIGINT received\n");
    sigint_count++;

    if (sigint_count >= 3) {
        printf("Received SIGINT 3 times, exiting...\n");
        _exit(0);
    }
}

int main() {
    signal(SIGINT, sigint_handler);
    
    printf("Press Ctrl+C to send SIGINT...\n");
    
    while (1) {
        sleep(1);
    }
    return 0;
}