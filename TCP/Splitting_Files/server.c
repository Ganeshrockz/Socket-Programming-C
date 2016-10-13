#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include"request.h"

#define PORT 3062

int main()
{
    int client, server;
    FILE *ptr_readfile;
    char line[128];
    int bin, lis, acc;
    struct sockaddr_in clientSocket, serverSocket;
    struct request clientRequest;
    socklen_t clientLength;
    server = socket(AF_INET, SOCK_STREAM, 0);

    bzero((struct sockaddr*) &serverSocket, sizeof(serverSocket));
    bzero((struct sockaddr*) &clientSocket, sizeof(clientSocket));

    serverSocket.sin_port = htons(PORT);
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_addr.s_addr = htons(INADDR_ANY);

    bin = bind(server, (struct sockaddr*) &serverSocket, sizeof(serverSocket));

    lis = listen(server,10);

    clientLength = sizeof(clientSocket);

    client = accept(server, (struct sockaddr*) &clientSocket, &clientLength);

    read(client, (struct request*) &clientRequest, sizeof(clientRequest));
    fflush(stdout);
    ptr_readfile = fopen(clientRequest.file_name, "r");
    printf("File Name: %s\n", clientRequest.file_name);
    printf("Buffer Size: %d\n", clientRequest.buffer);
    while(fgets(line, clientRequest.buffer, ptr_readfile))
    {
        write(client, line, sizeof(line));
    }
    strcpy(line, "bye");
    write(client, line, sizeof(line));

    close(client);
    close(server);
    fclose(ptr_readfile);

    return 0;
}
