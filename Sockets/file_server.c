#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_sock) {
    char filename[BUFFER_SIZE];
    char file_buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE * 2];
    
    // Read filename requested by client
    int bytes_read = read(client_sock, filename, sizeof(filename) - 1);
    if (bytes_read <= 0) {
        close(client_sock);
        return;
    }
    filename[bytes_read] = '\0';
    // Remove trailing newline if present
    filename[strcspn(filename, "\r\n")] = 0;

    printf("Client requested file: '%s'\n", filename);

    FILE *file = fopen(filename, "r");
    pid_t pid = getpid(); // Get child process ID

    if (file == NULL) {
        // Send Error message + PID
        sprintf(response, "[Server PID: %d] Error: File '%s' not found.\n", pid, filename);
        write(client_sock, response, strlen(response));
    } else {
        // Send PID acknowledgment first
        sprintf(response, "[Server PID: %d] File contents follow:\n---\n", pid);
        write(client_sock, response, strlen(response));

        // Read file contents and stream to client
        while (fgets(file_buffer, sizeof(file_buffer), file) != NULL) {
            write(client_sock, file_buffer, strlen(file_buffer));
        }
        fclose(file);
    }
    close(client_sock);
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    printf("TCP File Server running on port %d...\n", PORT);

    while (1) {
        if ((client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept error");
            continue;
        }

        // Fork to handle concurrency
        pid_t pid = fork();
        if (pid == 0) { // Child Process
            close(server_fd); // Child doesn't need the listener socket
            handle_client(client_sock);
            exit(0); // Terminate child process when done
        } else if (pid > 0) { // Parent Process
            close(client_sock); // Parent doesn't need this specific client socket
        } else {
            perror("Fork failed");
        }
    }
    return 0;
}
