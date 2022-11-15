#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main () {
    int sockfd;
    char buff[MAXLINE];
    char *msg = "Hello from client 1";
    struct sockaddr_in server_addr;

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed!");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    int n, len;
    sendto(sockfd, (const char *)msg, strlen(msg), 0, (const struct sockaddr *) &server_addr, sizeof(server_addr)); 
    printf("Hello message sent!\n");

    close(sockfd);
    return 0;
}