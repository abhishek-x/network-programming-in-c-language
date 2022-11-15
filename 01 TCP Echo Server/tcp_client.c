#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main (int argc, char ** argv) {
    int sockfd, n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    int client_fd = connect(sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));

    while (1) {
        bzero(sendline, 100);
        bzero(recvline, 100);
        fgets(sendline, 100, stdin);
        send(sockfd, sendline, strlen(sendline), 0);
        recv(sockfd, recvline, 100, 0);
        printf("%s", recvline);
    }

    return 0;
}