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
    struct sockaddr_in server_addr, client_addr1, client_addr2;

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed!");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr1, 0, sizeof(client_addr1));
    memset(&client_addr2, 0, sizeof(client_addr2));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Bind Failed!");
        exit(EXIT_FAILURE);
    }

    int n, len1, len2;
    len1 = sizeof(client_addr1);
    bzero(&buff, sizeof(buff));
    n = recvfrom(sockfd, (char *)buff, MAXLINE,  0, ( struct sockaddr *) &client_addr1, &len1); 
    buff[n] = '\0'; 
    printf("Client 1: %s\n", buff); 
    len1 = sizeof(client_addr2);
    bzero(&buff, sizeof(buff));
    n = recvfrom(sockfd, (char *)buff, MAXLINE,  0, ( struct sockaddr *) &client_addr2, &len2); 
    buff[n] = '\0'; 
    printf("Client 2: %s\n", buff); 

    return 0;
}