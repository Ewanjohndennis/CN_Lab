#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 2048

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    char reply[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter new-gen English sentence:\n> ");
    fgets(buffer, sizeof(buffer), stdin);

    // Send original text to server
    sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, addr_len);

    // Receive translated formal text
    int n = recvfrom(sockfd, reply, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
    reply[n] = '\0';

    printf("\nTranslated Sentence:\n%s\n", reply);

    close(sockfd);
    return 0;
}
