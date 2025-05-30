#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child process: My PID is %d\n", getpid());
    } else {
        printf("Parent process: Child PID is %d\n", pid);
    }
    return 0;
}