#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int signal_count = 0;

void sigusr1_handler(int sig) {
    printf("Received signal from parent\n");
}

int main() {
    pid_t pid;
    
    pid = fork();
    
    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        signal(SIGUSR1, sigusr1_handler);
        while (1) {
            sleep(1);
        }
    }
    else {
        while (signal_count < 5) {
            sleep(2);
            kill(pid, SIGUSR1);
            signal_count++;
            printf("Parent sent SIGUSR1 (%d/5)\n", signal_count);
        }
        kill(pid, SIGTERM);
        printf("Program finished after 5 signals\n");
        _exit(0);
    }
    return 0;
}