#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include"client.h"
#include"server.h"
#define PORT 3062

int main()
{
    socklen_t clientLength;
    int server,client;
    struct sockaddr_in serverSocket,clientLength;
    struct cli request;
    struct ser response;
    int bin, lis;

    server = socket(AF_INET, SOCK_DGRAM, 0);
    



