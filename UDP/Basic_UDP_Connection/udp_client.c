#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 3062

int main()
{
    int client;
    socklen_t clientSize;
    struct sockaddr_in clientSocket;
    char buffer[1024];
    client = socket(AF_INET, SOCK_DGRAM, 0);
    
    bzero((struct sockaddr*) &clientSocket, sizeof(clientSocket));
    clientSocket.sin_family = AF_INET;
    clientSocket.sin_port = htons(PORT);
    clientSocket.sin_addr.s_addr = htons(INADDR_ANY);


    clientSize = sizeof(clientSocket);
    
    while(1)
    {
        printf("Client Message: ");
        scanf("%s", buffer);
        
        
        sendto(client, buffer, sizeof(buffer), 0, (struct sockaddr*) &clientSocket, sizeof(clientSocket));
        
        if(strcmp(buffer,"bye") == 0)
            break;
        recvfrom(client, buffer, sizeof(buffer), 0, (struct sockaddr*) &clientSocket, &clientSize);

        printf("Server: %s\n", buffer);
        
    }

    close(client);
    return 0;
}



