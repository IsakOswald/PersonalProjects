#include <stdio.h>
#include <stdlib.h>
#include <string.h>      // For strlen.
#include <unistd.h>      // To close the socket.
#include <sys/socket.h>  // For the sockets.
#include <netinet/in.h>  //For the IPv4 struct.
#include <arpa/inet.h>   // For the inet_addr (pass IP's correctly).

// Specify an address for the socket to connect to (in our case a server).
struct sockaddr_in serverAddr;

int main()
{
    // Create a socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);  // AF_INET specifies an IPv4 and SOCK_STREAM specifies to use the TCP protocol.

    // Setting up the connection paramaters
    serverAddr.sin_family = AF_INET;                      // We will be connecting to an IPv4 host (server).
    serverAddr.sin_port = htons(8080);                    // Specify the port we want to connect over remotly. htons() makes sure its the appropriate format.
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Use the arpa/inet.h lib here to use inet_addr() to put our IP string to a real IP.

    // Connect using the configurations we supplied (port, IP, etc).
    if (connect(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)  // Typecaset sockaddr_in into jsut a sock_addr* (sock_adddr is just a "class base", pointer can hold any extension).
    {
        // Check if the connection failed.
        fprintf(stderr, "Error connecting socket to server \n");
        // Close socket and exit
        close(socketfd);
        exit(1);
    }

    char serverResp[256];

    recv(socketfd, &serverResp, sizeof(serverResp) - 1, 0);  // Recieve the incoming data from the server and save it into our buffer.

    if (strlen(serverResp) > 0)
    {
        serverResp[sizeof(serverResp) - 1] = '\0';
    
        printf("%s", serverResp);
    }

    else
    {
        printf("No data from the host was sent!");
    }


    close(socketfd);

    return 0;
}
