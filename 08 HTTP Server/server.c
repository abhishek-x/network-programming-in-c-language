#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 1024
#define BACKLOG 10  

void report(struct sockaddr_in *serverAddress);

void setHttpHeader(char httpHeader[])
{
    FILE *htmlData = fopen("./Website/index.html", "r");

    char line[100];
    char responseData[8000];
    while (fgets(line, 100, htmlData) != 0) {
        strcat(responseData, line);
    }
    strcat(httpHeader, responseData);
}

int main(void)
{
    FILE* ptr = fopen("config.txt", "r");
    if (ptr == NULL) {
        printf("no such file.");
        return 0;
    }

    char buf[100];
    int config[3];
    int i = 0;
    printf("\nReading Config.txt File:\n\n");
    while (fscanf(ptr, "%*s %s ", buf) == 1 && i < 3) {
        config[i] = atoi(buf);
        i++;
    }

    printf("...\tPORT_NO: %d\n...\tHTTP_HEADER_SIZE: %d\n...\tBACKLOG_QUEUE_LIMIT: %d\n\n", config[0], config[1], config[2]);

    char httpHeader[8000] = "HTTP/1.1 200 OK\r\n\n";

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        printf("Error: Failed to create socket.\n");
        exit(EXIT_FAILURE);
    } else printf("Success: Socket Created\n");

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8001);
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress))) {
        printf("Error: The socket failed to bind.\n");
        exit(EXIT_FAILURE);
    } else printf("Success: Socket Binded\n");

    int listening = listen(serverSocket, config[2]);
    if (listening < 0) {
        printf("Error: The server is not listening.\n");
        exit(EXIT_FAILURE);
    } else printf("Success: Server is Listening for clients.\n");

    char hostBuffer[INET6_ADDRSTRLEN];
    char serviceBuffer[NI_MAXSERV];
    socklen_t addr_len = sizeof(serverAddress);

    int err = getnameinfo((struct sockaddr *) &serverAddress, addr_len, hostBuffer, sizeof(hostBuffer), serviceBuffer, sizeof(serviceBuffer), NI_NUMERICHOST);
    if (err != 0) {
        printf("Error: Server is not working!!\n");
    }

    printf("\nSuccess: Server listening on http://%s:%d\n", hostBuffer, config[0]);

    setHttpHeader(httpHeader);
    int clientSocket;

    while(1) {
        clientSocket = accept(serverSocket, NULL, NULL);
        send(clientSocket, httpHeader, sizeof(httpHeader), 0);
        close(clientSocket);
    }
    return 0;
}