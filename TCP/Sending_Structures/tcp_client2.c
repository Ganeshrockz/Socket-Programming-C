#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include"s.h"
#include"c.h"

#define PORT 3062

int main()
{   
    struct serv resp;
    struct cli req;

    int client;
    int lis, conn;
    struct sockaddr_in clientSocket;
    char buffer[256];

    bzero((struct sockaddr*) &clientSocket, sizeof(clientSocket));

    clientSocket.sin_family = AF_INET;
    clientSocket.sin_port = htons(PORT);
    clientSocket.sin_addr.s_addr = htons(INADDR_ANY);

    client = socket(AF_INET, SOCK_STREAM, 0);

    if(client<0)
    {
        printf("Socket Failed to Create\n");
        exit(0);
    }

    printf("Connection Established\n");

    conn = connect(client, (struct sockaddr*) &clientSocket, sizeof(clientSocket));

    if(conn<0)
    {
        printf("Connection not established\n");
        exit(0);
    }

    printf("Connection Established..\n");

    listen(client, 10);
    do
    {
        printf("Enter the Name: ");
        scanf("%s", req.name);

        printf("Enter the Register Number: ");
        scanf("%s", req.reg_no);


        write(client, (struct clit*) &req, sizeof(req));
        //listen(client,10);

        read(client, (struct serv*) &resp, sizeof(resp));
        printf("Server ID: %d\n", resp.id);
        printf("Server Name: %s\n", resp.name);
        
    }while( (strcmp(resp.name, "bye") != 0) );

    close(client);
}
