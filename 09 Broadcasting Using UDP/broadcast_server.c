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

int main() {
    int server_socket;
    char *msg = "Hello from Server";
    struct sockaddr_in broadcast_address;

    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure: Socket Creation Failed\n");
        exit(EXIT_FAILURE);
    } else printf("Success: Socket Created Successfully\n");

    memset(&broadcast_address, 0, sizeof(broadcast_address));

    int value = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_BROADCAST, (const void *)&value, (socklen_t)sizeof(value));

    broadcast_address.sin_family = AF_INET;
    broadcast_address.sin_port = htons(PORT);
    broadcast_address.sin_addr.s_addr = inet_addr("172.20.10.15");

    sendto(server_socket, (const void*)msg, strlen(msg), 0, (const struct sockaddr *)&broadcast_address, sizeof(broadcast_address));
    printf("Success: Hello Message Sent\n");

    close(server_socket);
    return 0;
}