#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int client_fd;
    struct sockaddr_in server_addr;

    client_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        printf("Error: Socket Creation Error\n");
        exit(0);
    } else {
        printf("Socket created successfully...\n");
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (connect(client_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        printf("Connection with server failed!\n");
        exit(0);
    } else {
        printf("Successfully connected to server...\n");
    }

    char buff[10];
    int n;
    for (int i = 0; i < 2; i++) {
        bzero(buff, sizeof(buff));
        printf("Enter Number %d: ", i+1);
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        send(client_fd, buff, sizeof(buff), 0);
    }

    bzero(buff, sizeof(buff));
    printf("Sum of numbers is: ");
    recv(client_fd, buff, sizeof(buff), 0);
    printf("%s\n", buff);

    close(client_fd);
}