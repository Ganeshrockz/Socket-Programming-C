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
    FILE *ptr_writefile;
    char line[128], opname[15];
    int filecounter = 0;
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
    
    while(read(client,line,sizeof(line)))
    {
        //read(client, line, sizeof(line));
        if(strcmp(line, "bye") == 0)
            break;
        filecounter++;
        sprintf(opname, "file_part%d", filecounter);
        //conver the above line, second part from file_part%d to file_part%d.txt when working on windows
        ptr_writefile = fopen(opname, "w");
        fprintf(ptr_writefile, "%s\n", line);
        fclose(ptr_writefile);
    }
    close(client);
    fclose(ptr_writefile);

    return 0;

}
