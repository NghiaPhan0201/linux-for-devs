#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include "../include/chat_app.h"

ChatApp app;

void init_server(int port) {
    app.server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (app.server_socket < 0) {
        perror("Error creating server socket");
        _exit(1);
    }

    int opt = 1;
    if (setsockopt(app.server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Error setting SO_REUSEADDR");
        close(app.server_socket);
        _exit(1);
    }
#ifdef SO_REUSEPORT
    if (setsockopt(app.server_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("Error setting SO_REUSEPORT");
        close(app.server_socket);
        _exit(1);
    }
#endif

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(app.server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Error binding server socket to port %d: %s\n", port, strerror(errno));
        close(app.server_socket);
        _exit(1);
    }

    if (listen(app.server_socket, 5) < 0) {
        perror("Error listening on server socket");
        close(app.server_socket);
        _exit(1);
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Error creating socket for IP retrieval");
        _exit(1);
    }

    struct ifreq ifr;
    strncpy(ifr.ifr_name, "enp0s3", IFNAMSIZ-1);
    ifr.ifr_name[IFNAMSIZ-1] = '\0';

    if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
        perror("Error getting IP address");
        close(sock);
        _exit(1);
    }

    struct sockaddr_in *ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
    inet_ntop(AF_INET, &ipaddr->sin_addr, app.host, INET_ADDRSTRLEN);
    close(sock);

    app.port = port;
    app.conn_id_counter = 0;
    app.running = 1;
    pthread_mutex_init(&app.lock, NULL);

    printf("Server listening on %s:%d\n", app.host, port);

    pthread_t accept_thread;
    pthread_create(&accept_thread, NULL, accept_connections, NULL);
    pthread_detach(accept_thread);
}

void *accept_connections(void *arg) {
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    static int connection_count = 0; // Track connections
    while (app.running) {
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        setsockopt(app.server_socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

        int client_socket = accept(app.server_socket, (struct sockaddr*)&client_addr, &addr_len);
        if (!app.running) {
            if (client_socket >= 0) close(client_socket);
            break;
        }
        if (client_socket < 0) {
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
                perror("Error accepting connection");
            }
            continue;
        }

        pthread_mutex_lock(&app.lock);
        if (connection_count >= MAX_CONNECTIONS) {
            printf("Error: Maximum connections reached\n");
            close(client_socket);
            pthread_mutex_unlock(&app.lock);
            continue;
        }
        connection_count++;
        pthread_mutex_unlock(&app.lock);

        int conn_id = ++app.conn_id_counter;
        add_connection(client_socket, client_addr, conn_id);
        printf("DEBUG: Created thread for connection ID %d\n", conn_id);

        pthread_t client_thread;
        int *args = malloc(sizeof(int) * 2);
        if (!args) {
            perror("Error allocating memory");
            close(client_socket);
            pthread_mutex_lock(&app.lock);
            connection_count--;
            pthread_mutex_unlock(&app.lock);
            continue;
        }
        args[0] = client_socket;
        args[1] = conn_id;
        pthread_create(&client_thread, NULL, handle_client, args);
        pthread_detach(client_thread);
    }
    return NULL;
}

void *handle_client(void *arg) {
    int *args = (int*)arg;
    int client_socket = args[0];
    int conn_id = args[1];
    free(args);

    printf("DEBUG: Handling client thread for ID %d\n", conn_id);
    int flags = fcntl(client_socket, F_GETFL, 0);
    if (flags < 0 || fcntl(client_socket, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("Error setting socket to non-blocking");
        close(client_socket);
        return NULL;
    }

    char buffer[MAX_MESSAGE_LEN + 1];
    while (app.running) {
        int bytes = recv(client_socket, buffer, MAX_MESSAGE_LEN, 0);
        if (bytes < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                usleep(10000);
                if (!app.running) break;
                continue;
            }
            break;
        } else if (bytes == 0) {
            break;
        }
        buffer[bytes] = '\0';
        pthread_mutex_lock(&app.lock);
        for (int i = 0; i < MAX_CONNECTIONS; i++) {
            if (app.connections[i].active && app.connections[i].id == conn_id) {
                printf("Message received from %s\n", inet_ntoa(app.connections[i].addr.sin_addr));
                printf("Sender’s Port: %d\n", ntohs(app.connections[i].addr.sin_port));
                printf("Message: \"%s\"\n", buffer);
                break;
            }
        }
        pthread_mutex_unlock(&app.lock);
    }

    // Cleanup
    pthread_mutex_lock(&app.lock);
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (app.connections[i].active && app.connections[i].id == conn_id) {
            shutdown(client_socket, SHUT_RDWR);
            close(client_socket);
            printf("Connection %d (%s:%d) terminated\n", 
                   conn_id, inet_ntoa(app.connections[i].addr.sin_addr), 
                   ntohs(app.connections[i].addr.sin_port));
            app.connections[i].active = 0;
            app.connections[i].socket = -1;
            app.connections[i].id = 0;
            memset(&app.connections[i].addr, 0, sizeof(app.connections[i].addr));
            break;
        }
    }
    pthread_mutex_unlock(&app.lock);
    return NULL;
}

void connect_to_peer(const char *dest_ip, const char *dest_port) {
    if (!validate_ip(dest_ip)) {
        printf("Error: Invalid IP address\n");
        return;
    }

    int port;
    if (sscanf(dest_port, "%d", &port) != 1 || port < 0 || port > 65535) {
        printf("Error: Invalid port number\n");
        return;
    }

    if (strcmp(dest_ip, app.host) == 0 && port == app.port) {
        printf("Error: Cannot connect to self\n");
        return;
    }

    pthread_mutex_lock(&app.lock);
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (app.connections[i].active && 
            strcmp(inet_ntoa(app.connections[i].addr.sin_addr), dest_ip) == 0 &&
            ntohs(app.connections[i].addr.sin_port) == port) {
            printf("Error: Connection already exists\n");
            pthread_mutex_unlock(&app.lock);
            return;
        }
    }
    pthread_mutex_unlock(&app.lock);

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error creating client socket");
        return;
    }

    struct sockaddr_in peer_addr;
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, dest_ip, &peer_addr.sin_addr) <= 0) {
        printf("Error: Invalid IP address\n");
        close(client_socket);
        return;
    }

    if (connect(client_socket, (struct sockaddr*)&peer_addr, sizeof(peer_addr)) < 0) {
        perror("Error connecting to peer");
        close(client_socket);
        return;
    }

    int conn_id = ++app.conn_id_counter;
    add_connection(client_socket, peer_addr, conn_id);

    printf("Connected to %s:%d (ID: %d)\n", dest_ip, port, conn_id);

    pthread_t client_thread;
    int *args = malloc(sizeof(int) * 2);
    if (!args) {
        perror("Error allocating memory");
        close(client_socket);
        remove_connection(conn_id);
        return;
    }
    args[0] = client_socket;
    args[1] = conn_id;
    pthread_create(&client_thread, NULL, handle_client, args);
    pthread_detach(client_thread);
}

void send_message(const char *conn_id_str, const char *message) {
    int conn_id;
    if (sscanf(conn_id_str, "%d", &conn_id) != 1) {
        printf("Error: Invalid connection ID\n");
        return;
    }

    if (strlen(message) > MAX_MESSAGE_LEN) {
        printf("Error: Message exceeds %d characters\n", MAX_MESSAGE_LEN);
        return;
    }

    pthread_mutex_lock(&app.lock);
    int found = 0;
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (app.connections[i].active && app.connections[i].id == conn_id) {
            found = 1;
            int sent = send(app.connections[i].socket, message, strlen(message), 0);
            if (sent < 0) {
                perror("Error sending message");
                shutdown(app.connections[i].socket, SHUT_RDWR);
                close(app.connections[i].socket);
                printf("Connection %d (%s:%d) terminated\n", 
                       conn_id, inet_ntoa(app.connections[i].addr.sin_addr), 
                       ntohs(app.connections[i].addr.sin_port));
                app.connections[i].active = 0;
                app.connections[i].socket = -1;
                app.connections[i].id = 0;
                memset(&app.connections[i].addr, 0, sizeof(app.connections[i].addr));
            } else {
                printf("Message sent to %d\n", conn_id);
            }
            break;
        }
    }
    if (!found) {
        printf("Error: Connection ID %d does not exist\n", conn_id);
    }
    pthread_mutex_unlock(&app.lock);
}
