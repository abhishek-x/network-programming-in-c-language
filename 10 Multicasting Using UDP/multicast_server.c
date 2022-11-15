#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 5435
#define MAXLEN 1024

int main() {
    int sockfd;
    struct sockaddr_in addr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failed: Socket Creation Failed\n");
        exit(EXIT_FAILURE);
    } else printf("Success: Socket created successfully\n");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("226.1.2.3");

    struct in_addr local_interface;
    local_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&local_interface, sizeof(local_interface));

    char buffer[MAXLEN];
    memset(buffer, 0, sizeof(buffer));
    printf("Enter Multicast Message: ");
    int n = 0;
    while ((buffer[n++] = getchar()) != '\n');
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&addr, sizeof(addr));

    close(sockfd);
    return 0;
}