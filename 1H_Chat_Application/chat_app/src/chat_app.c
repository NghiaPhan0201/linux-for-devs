#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h> // For signal handling
#include "../include/chat_app.h"

extern ChatApp app;

void help() {
    printf("\nAvailable commands:\n");
    printf("  help                - Display this help message\n");
    printf("  myip                - Display the IP address of this machine\n");
    printf("  myport              - Display the port this program is listening on\n");
    printf("  connect <ip> <port> - Connect to a peer at the specified IP and port\n");
    printf("  list                - List all active connections\n");
    printf("  terminate <id>      - Terminate the connection with the specified ID\n");
    printf("  send <id> <message> - Send a message to the connection with the specified ID\n");
    printf("  exit                - Close all connections and exit the program\n");
}

void myip() {
    printf("My IP address: %s\n", app.host);
}

void myport() {
    printf("My port: %d\n", app.port);
}

void exit_app() {
    app.running = 0;

    // Lock to safely modify connection state
    pthread_mutex_lock(&app.lock);

    // Shutdown and close all client sockets
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (app.connections[i].active) {
            shutdown(app.connections[i].socket, SHUT_RDWR);
            close(app.connections[i].socket);
            app.connections[i].active = 0;
            app.connections[i].socket = -1;
            app.connections[i].id = 0;
            memset(&app.connections[i].addr, 0, sizeof(app.connections[i].addr));
        }
    }

    // Shutdown and close server socket
    if (app.server_socket >= 0) {
        shutdown(app.server_socket, SHUT_RDWR);
        close(app.server_socket);
        app.server_socket = -1;
    }

    pthread_mutex_unlock(&app.lock);

    // Destroy mutex
    pthread_mutex_destroy(&app.lock);

    printf("Exiting application\n");
    usleep(300000); // Allow threads to terminate (300ms)

    // Force exit
    _exit(0); // Use _exit to bypass atexit handlers
}

void process_command(char *input) {
    trim(input);
    if (strlen(input) == 0) return;

    char *cmd = strtok(input, " ");
    if (!cmd) return;

    if (strcmp(cmd, "help") == 0) {
        help();
    } else if (strcmp(cmd, "myip") == 0) {
        myip();
    } else if (strcmp(cmd, "myport") == 0) {
        myport();
    } else if (strcmp(cmd, "connect") == 0) {
        char *ip = strtok(NULL, " ");
        char *port = strtok(NULL, " ");
        if (ip && port && !strtok(NULL, " ")) {
            connect_to_peer(ip, port);
        } else {
            printf("Usage: connect <ip> <port>\n");
        }
    } else if (strcmp(cmd, "list") == 0) {
        list_connections();
    } else if (strcmp(cmd, "terminate") == 0) {
        char *conn_id = strtok(NULL, " ");
        if (conn_id && !strtok(NULL, " ")) {
            remove_connection(atoi(conn_id));
        } else {
            printf("Usage: terminate <id>\n");
        }
    } else if (strcmp(cmd, "send") == 0) {
        char *conn_id = strtok(NULL, " ");
        char *message = strtok(NULL, "");
        if (conn_id && message) {
            send_message(conn_id, message);
        } else {
            printf("Usage: send <id> <message>\n");
        }
    } else if (strcmp(cmd, "exit") == 0) {
        exit_app();
    } else {
        printf("Invalid command. Type 'help' for a list of commands.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port;
    if (sscanf(argv[1], "%d", &port) != 1 || port < 0 || port > 65535) {
        fprintf(stderr, "Error: Port must be a valid number between 0 and 65535\n");
        return 1;
    }

    // Initialize server socket to -1
    app.server_socket = -1;
    init_server(port);
    init_connections();
    printf("\n");
    help();

    char input[MAX_INPUT];
    while (app.running) {
        printf("> ");
        fflush(stdout);
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            exit_app();
        }
        process_command(input);
    }

    return 0;
}
