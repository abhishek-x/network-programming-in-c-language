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

int main(int argc, char const * argv[]) {
    int sock, client_fd, valread;
    struct sockaddr_in saddr;
    char *hello = "Hello From Client!";
    char buffer[1024] = {0};

    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket Creation Failed!");
        return -1;
    }

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr) <= 0) {
        printf("Invalid Address / Address Not Supported!");
        return -1;
    }

    if ((client_fd = connect(sock, (const struct sockaddr *) &saddr, sizeof(saddr))) < 0) {
        printf("Connection Failed!");
        return -1;
    }

    send(sock, hello, strlen(hello), 0);
    printf("Hello Message Sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    close(client_fd);
    
    return 0;
}