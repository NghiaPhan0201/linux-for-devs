#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0
        printf("Child process: My PID is %d, Parent PID is %d\n", getpid(), getppid());
        sleep(10);
        printf("Child process: My new Parent PID is %d after parent exits\n", getppid());
        exit(0);
    } else {
        printf("Parent process: My PID is %d, Child PID is %d\n", getpid(), pid);
        sleep(2);
        printf("Parent process: Exiting\n");
        exit(0);
    }
    return 0;
}