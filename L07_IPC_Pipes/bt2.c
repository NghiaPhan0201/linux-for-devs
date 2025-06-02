#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe1[2];
    int pipe2[2];
    pid_t pid1, pid2;
    char buffer1[100];
    char buffer2[100];
    char *message = "Hello from parent";

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 > 0) {
        close(pipe1[0]);
        write(pipe1[1], message, strlen(message) + 1);
        close(pipe1[1]);
    } else {
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 > 0) {
            close(pipe1[1]);
            close(pipe2[0]);
            read(pipe1[0], buffer1, sizeof(buffer1));
            strcat(buffer1, " - modified by child 1");
            write(pipe2[1], buffer1, strlen(buffer1) + 1);
            close(pipe1[0]);
            close(pipe2[1]);
        } else {
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[1]);
            read(pipe2[0], buffer2, sizeof(buffer2));
            printf("Child 2 received: %s\n", buffer2);
            close(pipe2[0]);
        }
    }

    return 0;
}