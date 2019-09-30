#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) 
{
    //Stream sockets and rcv()

    struct addrinfo addrinfo;
    struct addrinfo *addr = NULL;
    int sockfd;

    char buf[2056];
    int byte_count;

    sockfd = socket(AF_INET, SOCK_STREAM, STDIN_FILENO);

    //get host info, make socket and connect it
    memset(&addrinfo, 0, sizeof(addrinfo));
    addrinfo.ai_family = AF_INET;
    addrinfo.ai_socktype = SOCK_STREAM;

    getaddrinfo("www.example.com", "80", &addrinfo, &addr);
    
    printf("Connecting...\n");
    connect(sockfd,addr->ai_addr,addr->ai_addrlen);
    printf("Connected!\n");

    // char *header = "GET /postgrad/documents/cribphdmay.doc HTTP/1.0\r\n" \
    //                "Host: www.canterbury.ac.nz\r\n";

    char *header = "GET /sqlrest/CUSTOMER/3/ HTTP/1.0\r\nHost: www.thomas-bayer.com\r\n\r\n";
    send(sockfd,header,strlen(header),0);

    // send(sockfd, header ,sizeof(header),0);
    printf("GET Sent...\n");

    //all right ! now that we're connected, we can receive some data!
    byte_count = recv(sockfd, buf,sizeof(buf)-1, 0); // <-- -1 to leave room for a null terminator
    buf[byte_count] = 0; // <-- add the null terminator
    printf("recv()'d %d bytes of data in buf\n",byte_count);
    printf("%s\n\n\n",buf);
    // byte_count = recv(sockfd, buf, sizeof(buf),0);
    // printf("recv()'d %d bytes of data in buf\n",byte_count);
    // printf("%s",buf);

    return 0;
}