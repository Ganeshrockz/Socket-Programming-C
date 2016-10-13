#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>

#define PORT 3062

int main()
{
    int client;
    int lis, conn;
    struct sockaddr_in clientSocket;
    char buffer[1024];
    
    bzero((struct sockaddr*) &clientSocket, sizeof(clientSocket));

    client = socket(AF_INET, SOCK_STREAM, 0);

    if(client<0)
        printf("Socket creation failed\n");

    clientSocket.sin_family = AF_INET;
    clientSocket.sin_port = htons(PORT);
    clientSocket.sin_addr.s_addr = htons(INADDR_ANY);

    conn = connect(client, (struct sockaddr*) &clientSocket, sizeof(clientSocket));

    if(conn<0)
        printf("Connection Failed to Establish\n");

    do
    {
        printf("Enter the client Message: ");
        fgets(buffer, 1024, stdin);
        
        write(client, buffer, sizeof(buffer));
        listen(client,1);

        read(client, buffer, sizeof(buffer));
        printf("Server: %s\n", buffer);

    }while( (strcmp(buffer,"bye") !=0) );

    //close(clientSocket);
    close(client);
    return 0;
}


