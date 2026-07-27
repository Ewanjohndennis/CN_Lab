#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sockfd;
    struct sockaddr_in server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    int n = 3;

    printf("Enter the order of matrix: %d\n\n", n);

    int a[10][10] = {
        {1,2,3},
        {0,4,5},
        {0,0,6}
    };

    printf("Generated Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }

    send(sockfd, &n, sizeof(int), 0);
    send(sockfd, a, sizeof(a), 0);

    printf("\nMatrix sent successfully.\n");

    char result[50];
    recv(sockfd, result, sizeof(result), 0);

    printf("\nServer Response:\n%s\n", result);

    close(sockfd);

    return 0;
}