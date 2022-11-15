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
#define BACKLOG_QUEUE_LIMIT 100
#define MAXLEN 1024

int decimalToBinary(int num) {
  int binary = 0;
  int rem, i = 1;

  while (num != 0) {
    rem = num % 2;
    num /= 2;
    binary += rem * i;
    i *= 10;
  }

  return binary;
}

int main() {
    int server_fd, connection_fd;
    struct sockaddr_in server_addr, client_addr;

    server_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        printf("Error: Socket Creation failed!!!\n");
        exit(0);
    } else {
        printf("Socket Successfully Created...\n");
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
        printf("Error: Server failed to Bind!!!\n");
        exit(0);
    } else {
        printf("Socket successfully binded...\n");
    }

    if (listen(server_fd, BACKLOG_QUEUE_LIMIT) != 0) {
        printf("Error: Server failed to Listen!!!\n");
        exit(0);
    } else {
        printf("Server listening for new connections...\n");
    }

    int len = sizeof(client_addr);
    connection_fd = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t *) &len);
    if (connection_fd < 0) {
        printf("Error: Server failed to connect to client!!!\n");
        exit(0);
    } else {
        printf("Server successfully connected to the client...\n");
    }

    char buffer[1024];
    memset(&buffer, 0, sizeof(buffer));
    recv(connection_fd, &buffer, sizeof(buffer), 0);
    printf("Decimal Number: %s\n", buffer);

    int num = atoi(buffer);
    int bin = decimalToBinary(num);
    memset(&buffer, 0, sizeof(buffer));
    sprintf(buffer, "%d", bin);
    printf("Binary Number: %s\n", buffer);

    send(connection_fd, &buffer, sizeof(buffer), 0);

    close(server_fd);

    return 0;
}