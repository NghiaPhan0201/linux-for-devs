#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "../include/tcp_server.h"

int main() {
    int server_fd;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    handle_client(server_fd);

    close(server_fd);
    return 0;
}