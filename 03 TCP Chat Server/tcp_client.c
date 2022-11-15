#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX 80

int main() {
    int sockfd, connfd;
    struct sockaddr_in server_addr, cli;

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed!\n");
        exit(0);
    } else {
        printf("Socket successfully created...\n");
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
        printf("Connection with server failed!\n");
        exit(0);
    } else {
        printf("Successfully connected to server...\n\n--------Chat Started--------\n");
    }

    char buff[MAX];
    int n;

    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Client: ");
        n = 0;
        while((buff[n++] = getchar()) != '\n');
        send(sockfd, buff, sizeof(buff), 0);

        bzero(buff, sizeof(buff));
        recv(sockfd, buff, sizeof(buff), 0);
        printf("Server: %s", buff);

        if (strncmp(buff, "exit", 4) == 0) {
            printf("Client exit!\n");
            break;
        }

    }

    close(sockfd);

    return 0;
}