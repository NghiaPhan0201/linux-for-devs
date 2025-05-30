#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child process: My PID is %d\n", getpid());
        sleep(2);
        exit(42);
    } else {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Parent process: Child PID %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("Parent process: Child did not exit normally\n");
        }
    }
    return 0;
}