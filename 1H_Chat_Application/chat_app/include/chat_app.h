#ifndef CHAT_APP_H
#define CHAT_APP_H

#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_MESSAGE_LEN 100
#define MAX_CONNECTIONS 10
#define MAX_INPUT 1024

// Structure for a single connection
typedef struct {
    int id;
    int socket;
    struct sockaddr_in addr;
    int active;
} Connection;

// Global application state
typedef struct {
    int server_socket;
    char host[INET_ADDRSTRLEN];
    int port;
    Connection connections[MAX_CONNECTIONS];
    int conn_id_counter;
    int running;
    pthread_mutex_t lock;
} ChatApp;

// Function prototypes (connection.c)
void init_connections();
void add_connection(int socket, struct sockaddr_in addr, int conn_id);
void remove_connection(int conn_id);
void list_connections();

// Function prototypes (network.c)
void init_server(int port);
void *accept_connections(void *arg);
void *handle_client(void *arg);
void connect_to_peer(const char *dest_ip, const char *dest_port);
void send_message(const char *conn_id_str, const char *message);

// Function prototypes (utils.c)
int validate_ip(const char *ip);
void trim(char *str);

// Function prototypes (chat_app.c)
void process_command(char *input);
void help();
void myip();
void myport();
void exit_app();

#endif