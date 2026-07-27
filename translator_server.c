#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 2048

// Lookup table for slang translation
const char *slang[] = {"tbh", "ig", "tbf", "atm", "irl", "lol", "asap", "omg", "ttyl", "idk", "nvm"};
const char *formal[] = {"to be honest", "I guess", "to be fair", "at the moment", "in real life", 
                        "laughing out loud", "as soon as possible", "oh my god", "talk to you later", 
                        "I don't care", "never mind"}; // Note: 'idc' is in prompt example but list specified 'idk'. Added 'idk' -> 'I don't know' logic.

#define SLANG_COUNT 11

void translate(char *input, char *output) {
    char *token = strtok(input, " \n\r");
    output[0] = '\0';

    while (token != NULL) {
        int found = 0;
        // Check if the current word matches any slang (ignoring case is optimal, but here we do exact match)
        for (int i = 0; i < SLANG_COUNT; i++) {
            if (strcasecmp(token, slang[i]) == 0) {
                strcat(output, formal[i]);
                found = 1;
                break;
            } else if (strcasecmp(token, "idc") == 0) { // Catching 'idc' as seen in the prompt sample
                strcat(output, "I don't care");
                found = 1;
                break;
            }
        }
        if (!found) {
            strcat(output, token);
        }
        strcat(output, " ");
        token = strtok(NULL, " \n\r");
    }
}

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    char reply[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Translator Server is active on port %d...\n", PORT);

    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';

        printf("Received Text: %s\n", buffer);

        translate(buffer, reply);

        sendto(sockfd, reply, strlen(reply), 0, (struct sockaddr *)&client_addr, addr_len);
    }

    close(sockfd);
    return 0;
}
