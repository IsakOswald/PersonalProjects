#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct sockaddr_in serverAddr;

int main()
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        fprintf(stderr, "Error conneting to host!\n");
        exit(1);
    }

    printf("Connection success");

    char serverResp[256];

    size_t bytesRecvd = recv(socketfd, &serverResp, sizeof(serverResp) - 1, 0);

    if (bytesRecvd < 0)
    {
        close(socketfd);
        exit(1);
    }

    serverResp[bytesRecvd] = '\0';

    printf("%s", serverResp);

    close(socketfd);

    return 0;
}
