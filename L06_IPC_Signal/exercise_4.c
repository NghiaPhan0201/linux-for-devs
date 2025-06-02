#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigtstp_handler(int sig) {
    printf("SIGTSTP ignored\n");
}

int main() {
    signal(SIGTSTP, sigtstp_handler);
    
    printf("Press Ctrl+Z to test SIGTSTP (will be ignored)...\n");
    while (1) {
        printf("Program is running...\n");
        sleep(1);
    }
    return 0;
}