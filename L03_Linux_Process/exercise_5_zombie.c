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
        sleep(10);
        printf("Child process: Exiting\n");
        exit(0);
    } else {
        printf("Parent process: My PID is %d, Child PID is %d\n", getpid(), pid);
        sleep(2);
        printf("Parent process: Exiting\n");
        exit(0);
    }
    return 0;
}