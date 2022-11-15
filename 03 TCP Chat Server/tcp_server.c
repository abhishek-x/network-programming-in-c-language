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
#define BACKLOG_QUEUE_LIMIT 5
#define MAX 80

int main() {
    int sockfd, connfd, len;
    struct sockaddr_in server_addr, cli;

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation error!\n");
        exit(0);
    } else {
        printf("Socket created successfully...\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if ((bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0)) {
        printf("Socked failed to bind!\n");
        exit(0);
    } else {
        printf("Socket successfully binded...\n");
    }

    if ((listen(sockfd, BACKLOG_QUEUE_LIMIT)) != 0) {
        printf("Socket failed to listen!\n");
        exit(0);
    } else {
        printf("Server listening...\n");
    }

    len = sizeof(cli);

    connfd = accept(sockfd, (struct sockaddr *) &cli, (socklen_t *) &len);
    if (connfd < 0) {
        printf("Server accept failed!\n");
        exit(0);
    } else {
        printf("Server accepted the client...\n\n--------Chat Started--------\n");
    }

    char buff[MAX];
    int n;

    for (;;) {
        bzero(buff, MAX);
        recv(connfd, buff, sizeof(buff), 0);
        printf("Client: %s", buff);

        bzero(buff, MAX);
        printf("Server: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        send(connfd, buff, sizeof(buff), 0);

        if (strncmp("exit", buff, 4) == 0) {
            printf("Server exit!\n");
            break;
        }
    }

    close(sockfd);

    return 0;
}