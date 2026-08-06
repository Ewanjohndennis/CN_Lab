#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);

    printf("Server started...\n");
    printf("Waiting for client...\n");

    newsockfd = accept(sockfd, (struct sockaddr *)&client, &len);
    printf("Client connected.\n");

    int n;
    recv(newsockfd, &n, sizeof(int), 0);

    int a[10][10];
    recv(newsockfd, a, sizeof(a), 0);

    printf("Received matrix of order %d.\n", n);

    int upper = 1, lower = 1, diagonal = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j && a[i][j] != 0)
                upper = 0;
            if (i < j && a[i][j] != 0)
                lower = 0;
            if (i != j && a[i][j] != 0)
                diagonal = 0;
        }
    }

    char result[50];

    if (diagonal)
        sprintf(result, "Diagonal Matrix");
    else if (upper)
        sprintf(result, "Upper Triangular Matrix");
    else if (lower)
        sprintf(result, "Lower Triangular Matrix");
    else
        sprintf(result, "Ordinary Matrix");

    printf("Matrix Type: %s\n", result);

    send(newsockfd, result, sizeof(result), 0);

    printf("Result sent to client.\n");

    close(newsockfd);
    close(sockfd);

    return 0;
}
