#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void signal_handler(int sig) {
    printf("Child process: Received SIGUSR1 signal\n");
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        signal(SIGUSR1, signal_handler);
        printf("Child process: My PID is %d, waiting for signal...\n", getpid());
        while (1) {
            pause();
        }
    } else {
        sleep(2);
        printf("Parent process: Sending SIGUSR1 to child PID %d\n", pid);
        kill(pid, SIGUSR1);
        sleep(1);
        kill(pid, SIGTERM);
        wait(NULL);
    }
    return 0;
}