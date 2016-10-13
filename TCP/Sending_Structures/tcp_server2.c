#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include"s.h"
#include"c.h"

#define PORT 3062

int main()
{   
    struct cli req;
    struct serv resp;

    int server, client;
    int bin, lis, acc;
    socklen_t cliLength;
    struct sockaddr_in serverSocket, clientSocket;
    char buff[256];
    bzero((struct sockaddr*) &serverSocket, sizeof(serverSocket));
    bzero((struct sockaddr*) &clientSocket, sizeof(clientSocket));

    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(PORT);
    serverSocket.sin_addr.s_addr = htons(INADDR_ANY);

    server = socket(AF_INET, SOCK_STREAM, 0);

    if(server<0)
    {
        printf("Failed to create Socket\n");
        exit(0);
    }

    bin = bind(server, (struct sockaddr*) &serverSocket, sizeof(serverSocket));

    if(bin<0)
    {
        printf("Binding Failed\n");
        exit(0);
    }

    printf("Socket Binded Successfully\n");

    lis = listen(server, 20);

    if(lis<0)
    {
        printf("Listening Failed\n");
        exit(0);
    }

    printf("Listening on port 3062\n");
    
    cliLength = sizeof(clientSocket);

    client = accept(server, (struct sockaddr*) &clientSocket, &cliLength);

    do
    {
        read(client,(struct clit*) &req, sizeof(req));
        
        printf("Client Name: %s\n", req.name);
        printf("Client Register Number: %s\n", req.reg_no);



        printf("Enter the server ID: ");
        scanf("%d", &resp.id);
        printf("Enter the server Name: ");
        scanf("%s", resp.name);


        write(client, (struct serv*) &resp, sizeof(resp) );
    }while( (strcmp(resp.name, "bye") != 0) );

    close(server);
    close(client);
}
                
