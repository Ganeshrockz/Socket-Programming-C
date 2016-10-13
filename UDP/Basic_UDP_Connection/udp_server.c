#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 3062
int main()
{   
    socklen_t clilen;
    int server;
    int bin,lis;
    struct sockaddr_in serverSocket, clientSocket;
    char buffer[1024];
    bzero((struct sockaddr*) &serverSocket, sizeof(serverSocket));
    bzero((struct sockaddr*) &clientSocket, sizeof(clientSocket));

    server = socket(AF_INET, SOCK_DGRAM, 0);

    if(server<0)
    {
        printf("Socket Creation Failed");
        exit(0);
    }
    
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_addr.s_addr = htons(INADDR_ANY);
    serverSocket.sin_port = htons(PORT);

    bin = bind(server, (struct sockaddr*) &serverSocket, sizeof(serverSocket));
    
    clilen = sizeof(clientSocket);

    while(1)
    {
        recvfrom(server, buffer, sizeof(buffer), 0, (struct sockaddr*) &clientSocket, &clilen);
        printf("Client: %s\n", buffer);

        //scanf("%s", buffer);
        if( strcmp(buffer,"bye") == 0) 
                break;
        scanf("%s",buffer);

        sendto(server, buffer, sizeof(buffer), 0, (struct sockaddr*) &clientSocket, clilen);
    }

    close(server);
    return 0;
}


        
