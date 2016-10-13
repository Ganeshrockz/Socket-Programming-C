#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define PORT 3062

int main()
{
    int client;
    int conn;
    struct sockaddr_in clientSocket;
    char buffer[1024];

    bzero((struct sockaddr*) &clientSocket, sizeof(clientSocket));

    client = socket(AF_INET, SOCK_STREAM, 0);

    clientSocket.sin_addr.s_addr = htons(INADDR_ANY);
    clientSocket.sin_family = AF_INET;
    clientSocket.sin_port = htons(PORT);
    
    
    conn = connect(client, (struct sockaddr*) &clientSocket, sizeof(clientSocket));
    
    printf("Enter the Client Message: ");
    scanf("%s", buffer);
    
    write(client,buffer,sizeof(buffer));

    read(client, buffer, sizeof(buffer));
    printf("Server: %s\n", buffer);

    close(client);
    return 0;
}
    
    


