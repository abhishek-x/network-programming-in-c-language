#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 8080
#define MAX_PENDING 3

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in saddr;
    int addrLen = sizeof(saddr);
    char buffer[1024] = {0};
    char *hello = "Hello From Server!";

    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket Creation Failed!");
        exit(EXIT_FAILURE);
    }

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(PORT);

    if ((bind(server_fd, (struct sockaddr *) &saddr, sizeof(saddr))) < 0) {
        perror("Failed to bind to socket!");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_PENDING) < 0) {
        perror("Failed to listen for new connections!");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *) &saddr, (socklen_t *) &addrLen)) < 0) {
        perror("Failed to Accept!");
        exit(EXIT_FAILURE);
    }

    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);

    send(new_socket, hello, strlen(hello), 0);
    printf("Hello Message Sent\n");

    close(new_socket);
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}