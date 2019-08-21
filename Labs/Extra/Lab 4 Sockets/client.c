#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <netdb.h> 
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>


#define MAXDATASIZE 1024 // max buffer size 
#define SERVER_PORT 2000


int client_socket(char *hostname)
{
    char port[20];
    struct addrinfo *their_addr = NULL; // connector's address information  
    struct addrinfo their_addrinfo;     // server address info

    int n = snprintf(port, 20, "%d", SERVER_PORT); // Make a string out of the port number
    if ((n < 0) || (n >= 20))
    {
        printf("ERROR: Malformed Port\n");
        exit(EXIT_FAILURE);
    }

    // 1) initialise socket using 'socket'
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);   

    // 2) initialise 'their_addrinfo' and use 'getaddrinfo' to lookup the IP from host name
    memset(&their_addrinfo, 0, sizeof(struct addrinfo));
    their_addrinfo.ai_family = AF_INET;         /* use an internet address */
    their_addrinfo.ai_socktype = SOCK_STREAM;   /* use TCP rather than datagram */

    sprintf(port, "%d", SERVER_PORT);
    getaddrinfo(hostname, port, &their_addrinfo, &their_addr);  /* get IP info */

    // 3) connect to remote host using 'connect'
    int rc = connect(sockfd, their_addr->ai_addr, their_addr->ai_addrlen);  // connect to server
    if(rc == -1) {
        perror("connect");
        exit(1);
    }
    
    return sockfd;
}


int main(int argc, char *argv[])
{
    char buffer[MAXDATASIZE];

    if (argc != 2) {  // counts the arguments
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    int sockfd = client_socket(argv[1]);

    int numbytes = 0;
    char *line;

    do {
        line = readline(">> ");

        // write and read from server
        write(sockfd, line, strlen(line));
        numbytes = read(sockfd, buffer, MAXDATASIZE - 1);

        buffer[numbytes] = '\0';

        printf("server: %s\n", buffer);

    } while (numbytes > 0);

    free(line);
    close(sockfd);

    return 0;
}
