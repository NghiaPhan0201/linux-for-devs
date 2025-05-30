#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        char *env_value = getenv("COMMAND_TYPE");
        if (env_value == NULL) {
            printf("No COMMAND_TYPE environment variable set\n");
            return 1;
        }

        if (env_value[0] == '1') {
            execlp("ls", "ls", NULL);
            perror("execlp ls failed");
        } else if (env_value[0] == '2') {
            execlp("date", "date", NULL);
            perror("execlp date failed");
        } else {
            printf("Unknown COMMAND_TYPE: %s\n", env_value);
        }
    } else {
        wait(NULL);
    }
    return 0;
}