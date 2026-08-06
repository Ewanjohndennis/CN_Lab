#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int client_sockets[MAX_CLIENTS];
int client_ids[MAX_CLIENTS];        // Tracks each client's ID number
int id_counter = 1;                 // Unique ID generator
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void add_client(int socket, int id) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] == 0) {
            client_sockets[i] = socket;
            client_ids[i] = id;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void remove_client(int socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] == socket) {
            client_sockets[i] = 0;
            client_ids[i] = 0;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void broadcast_message(char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    
    // Find the ID of the client who sent the message
    int sender_id = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] == sender_socket) {
            sender_id = client_ids[i];
            break;
        }
    }

    // Format the message with the sender tag
    char formatted_message[BUFFER_SIZE + 50];
    snprintf(formatted_message, sizeof(formatted_message), "[Client %d]: %s", sender_id, message);

    // Broadcast to all other connected clients
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] != 0 && client_sockets[i] != sender_socket) {
            send(client_sockets[i], formatted_message, strlen(formatted_message), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *socket_desc) {
    int sock = *(int *)socket_desc;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Safely generate and assign a unique ID for this client thread
    pthread_mutex_lock(&clients_mutex);
    int current_id = id_counter++;
    pthread_mutex_unlock(&clients_mutex);

    add_client(sock, current_id);
    printf("Client %d connected.\n", current_id);

    while ((bytes_read = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        broadcast_message(buffer, sock);
    }

    printf("Client %d disconnected.\n", current_id);
    remove_client(sock);
    close(sock);
    free(socket_desc);
    pthread_exit(NULL);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    printf("TCP Chat Server started on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        int *new_sock = malloc(sizeof(int));
        *new_sock = new_socket;
        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, (void *)new_sock);
        pthread_detach(thread);
    }
    return 0;
}
