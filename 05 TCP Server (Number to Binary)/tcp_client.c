#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 443
#define MAXLEN 1024

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

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (connect(client_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        printf("Connection with server failed!\n");
        exit(0);
    } else {
        printf("Successfully connected to server...\n");
    }

    char buffer[MAXLEN];
    int num;
    printf("Enter Decimal Number: ");
    scanf("%d", &num);
    
    memset(&buffer, 0, sizeof(buffer));
    sprintf(buffer, "%d", num);

    send(client_fd, &buffer, sizeof(buffer), 0);

    memset(&buffer, 0, sizeof(buffer));
    recv(client_fd, &buffer, sizeof(buffer), 0);
    printf("Decimal to Binary is: %s\n", buffer);

    close(client_fd);

    return 0;
}