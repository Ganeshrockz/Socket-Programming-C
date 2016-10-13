#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#define PORT 3062

void sending(int sockfd)
{   
    char buffer[1024];

    read(sockfd, buffer, sizeof(buffer));
    printf("Client Message: %s\n", buffer);

    printf("Enter a message: ");
    scanf("%s", buffer);

    write(sockfd, buffer, sizeof(buffer));
}

int main()
{   int pid;
    int client, server;
    struct sockaddr_in clientSocket, serverSocket;
    char buffer[1024];
    int bin, lis;
    socklen_t clientLength;
    bzero((struct sockaddr*) &serverSocket, sizeof(serverSocket));
    bzero((struct sockaddr*) &clientSocket, sizeof(clientSocket));

    server = socket(AF_INET, SOCK_STREAM, 0);

    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(PORT);
    serverSocket.sin_addr.s_addr = htons(INADDR_ANY);

    bin = bind(server, (struct sockaddr*) &serverSocket, sizeof(serverSocket));

    lis = listen(server, 15);
    clientLength = sizeof(clientSocket);
    
    while(1)
    {
        client = accept(server, (struct sockaddr*) &serverSocket, &clientLength);

        pid = fork();

        if(pid == 0)
        {
            close(server);
            sending(client);
            exit(0);
        }else
        {
            close(client);
        }
    }
    return 0;
}
        


