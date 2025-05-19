#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/chat_app.h"

extern ChatApp app;

void init_connections() {
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        app.connections[i].active = 0;
        app.connections[i].socket = -1;
    }
}

void add_connection(int socket, struct sockaddr_in addr, int conn_id) {
    pthread_mutex_lock(&app.lock);
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (!app.connections[i].active) {
            app.connections[i].id = conn_id;
            app.connections[i].socket = socket;
            app.connections[i].addr = addr;
            app.connections[i].active = 1;
            printf("New connection from %s:%d (ID: %d)\n", 
                   inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), conn_id);
            pthread_mutex_unlock(&app.lock);
            return;
        }
    }
    printf("Error: Maximum connections reached\n");
    close(socket);
    pthread_mutex_unlock(&app.lock);
}

void remove_connection(int conn_id) {
    pthread_mutex_lock(&app.lock);
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (app.connections[i].active && app.connections[i].id == conn_id) {
            shutdown(app.connections[i].socket, SHUT_RDWR);
            close(app.connections[i].socket);
            printf("Connection %d (%s:%d) terminated\n", 
                   conn_id, inet_ntoa(app.connections[i].addr.sin_addr), 
                   ntohs(app.connections[i].addr.sin_port));
            app.connections[i].active = 0;
            app.connections[i].socket = -1;
            app.connections[i].id = 0; // Reset ID
            pthread_mutex_unlock(&app.lock);
            return;
        }
    }
    printf("Error: Connection ID %d does not exist\n", conn_id);
    pthread_mutex_unlock(&app.lock);
}

void list_connections() {
    pthread_mutex_lock(&app.lock);
    int active = 0;
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (app.connections[i].active && app.connections[i].socket >= 0) {
            active++;
        }
    }
    if (active == 0) {
        printf("No active connections\n");
    } else {
        printf("id: IP address Port No.\n");
        for (int i = 0; i < MAX_CONNECTIONS; i++) {
            if (app.connections[i].active && app.connections[i].socket >= 0) {
                printf("%d: %s %d\n", 
                       app.connections[i].id, 
                       inet_ntoa(app.connections[i].addr.sin_addr), 
                       ntohs(app.connections[i].addr.sin_port));
            }
        }
    }
    pthread_mutex_unlock(&app.lock);
}