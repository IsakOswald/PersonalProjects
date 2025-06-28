#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

struct sockaddr_in serverAddr;

int main()
{
    char serverMessage[256] = "Hello from C2";

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to our IP and Port
    if (bind(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        fprintf(stderr, "Error binding socket");
        close(socketfd);
        exit(1);
    }

    listen(socketfd, 5);  // Second paramater is the backlog cap
    int clientSocket = accept(socketfd, NULL, NULL);

    send(clientSocket, serverMessage, sizeof(serverMessage), 0);

    close(socketfd);

    return 0;
}
