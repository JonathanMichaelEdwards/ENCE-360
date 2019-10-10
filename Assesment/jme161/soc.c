#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


void error(const char *msg) 
{
    perror(msg);
    exit(0);
}


int main(int argc, char *argv[]) 
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[10005];
    portno = 80;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    server = gethostbyname("www.google.com.au");
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }
    puts("Retreiving HTML Head");

    ssize_t nByte = write(sockfd, "HEAD / HTTP/1.0\r\nHost: www.google.com.au\r\n\r\n", strlen("HEAD / HTTP/1.1\r\n\r\n"));
    if (nByte <= 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    size_t recived_len = 0;
    if ((recived_len = read(sockfd, buffer, 10000)) > 0) {
        //bzero(buffer, 256);
        printf("%s\n\n", buffer);
        // printf("%ld\n\n", recived_len);
    }

    if (recived_len == -1) {
        perror("read");
    }

    close(sockfd);
    return 0;
}