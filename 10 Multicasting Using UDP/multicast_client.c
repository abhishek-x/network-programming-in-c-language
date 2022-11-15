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
    struct sockaddr_in local_socket_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Success: Socket created successfully\n");

    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));

    memset(&local_socket_addr, 0, sizeof(local_socket_addr));
    local_socket_addr.sin_family = AF_INET;
    local_socket_addr.sin_port = htons(PORT);
    local_socket_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&local_socket_addr, sizeof(local_socket_addr));
    printf("Binded Successfully\n");

    struct ip_mreq grp;
	grp.imr_multiaddr.s_addr = inet_addr("226.1.2.3");
	grp.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&grp, sizeof(grp));

    char buffer[MAXLEN];
	memset(buffer, 0, MAXLEN);
	read(sockfd, buffer, MAXLEN);
	printf("Message from multicast sender is: %s", buffer);

    return 0;
}