#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 5000
#define MAXLEN 1024

int main() {
    int sockfd;
    struct sockaddr_in addr;
    char buffer[MAXLEN];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure: Socket Creation Failed\n");
        exit(EXIT_FAILURE);
    } else printf("Success: Socket Created Successfully\n");

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (const struct sockaddr *)&addr, (socklen_t)sizeof(addr)) < 0) {
        perror("Failure: Socket Failed to Bind\n");
        exit(EXIT_FAILURE);
    } else printf("Success: Socket Binded Successfully\n");

    memset(buffer, 0, sizeof(buffer));
    int len = sizeof(addr);
    int n = recvfrom(sockfd, &buffer, MAXLEN, MSG_WAITALL, (struct sockaddr *)&addr, (socklen_t *)&len);
    buffer[n] = '\0';

    printf("Message: %s\n", buffer);

    close(sockfd);
    return 0;
}