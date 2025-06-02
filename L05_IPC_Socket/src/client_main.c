#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "../include/tcp_client.h"

int main() {
    int sock;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    communicate_with_server(sock);

    close(sock);
    return 0;
}