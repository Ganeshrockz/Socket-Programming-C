#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include"request.h"

#define PORT 3062

int main()
{
    int client;
    int conn, lis;
    struct sockaddr_in clientSocket;
    struct request clientRequest;
    
    printf("Enter the File Name: ");
    scanf("%s", clientRequest.file_name);
    printf("File Name: %s\n", clientRequest.file_name);

    printf("Enter the Buffer Size: ");
    scanf("%d", &clientRequest.buffer);
    printf("Buffer Size: %d\n", clientRequest.buffer);
    client = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero((struct sockaddr*) &clientSocket, sizeof(clientSocket));

    clientSocket.sin_addr.s_addr = htons(INADDR_ANY);
    clientSocket.sin_port = htons(PORT);
    clientSocket.sin_family = AF_INET;

    conn = connect(client, (struct sockaddr*) &clientSocket, sizeof(clientSocket));

    write(client, (struct request*) &clientRequest, sizeof(clientRequest));
    
    close(client);
    return 0;

}

