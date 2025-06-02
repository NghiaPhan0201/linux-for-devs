#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>

void sigint_handler(int sig) {
    printf("SIGINT received.\n");
}

void sigterm_handler(int sig) {
    printf("SIGTERM received, exiting...\n");
    _exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    
    fd_set readfds;
    char buffer[100];
    
    printf("Enter text (or wait for SIGINT/SIGTERM):\n");
    
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        
        struct timeval tv = {5, 0};
        
        int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
        
        if (ret == -1) {
            perror("select error");
            return 1;
        }
        else if (ret == 0) {
            printf("No input, still waiting...\n");
        }
        else if (FD_ISSET(STDIN_FILENO, &readfds)) {
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                printf("You entered: %s", buffer);
            }
        }
    }
    return 0;
}