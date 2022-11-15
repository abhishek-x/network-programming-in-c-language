#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8080
#define BACKLOG_QUEUE_LIMIT 100

int main() {
    int server_fd, connection_fd;
    struct sockaddr_in server_addr, client_addr;

    server_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        printf("Error: Socket Creation Error\n");
        exit(0);
    } else {
        printf("Socket created successfully...\n");
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
        printf("Error: Socket failed to bind\n");
        exit(0);
    } else {
        printf("Socket binded successfully...\n");
    }

    if (listen(server_fd, BACKLOG_QUEUE_LIMIT) != 0) {
        printf("Error: Socket failed to listen\n");
        exit(0);
    } else {
        printf("Server Listening...\n");
    }

    int len = sizeof(client_addr);
    connection_fd = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t *) &len);
    if (connection_fd < 0) {
        printf("Error: Server failed to accept client\n");
        exit(0);
    } else {
        printf("Server connected to client...\n");
    }

    char buff[10];
    int value[2];
    int n = 0;
    for (int i = 0; i < 2; i++) {
        bzero(buff, sizeof(buff));
        recv(connection_fd, buff, sizeof(buff), 0);
        printf("Recieved Number %d: %s", i+1, buff);
        value[i] = atoi(buff);
    }

    int val = value[0]+value[1];
    bzero(buff, sizeof(buff));
    sprintf(buff, "%d", val);

    send(connection_fd, buff, sizeof(buff), 0);

    close(server_fd);

    return 0;
}