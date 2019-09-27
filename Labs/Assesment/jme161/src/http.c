#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "http.h"


#define RANGE_LIMIT 500
#define BUF_SIZE 1024


size_t reserved = BUF_SIZE;


void append_buffer(Buffer *buffer, size_t length) 
{
	while ((length + buffer->length) < reserved) {
		reserved *= 2;
    	buffer->data = realloc(buffer->data, reserved);
	}
    buffer->length += length;

    return buffer;
}


/**
 * Perform an HTTP 1.0 query to a given host and page and port number.
 * host is a hostname and page is a path on the remote server. The query
 * will attempt to retrrecv(s, chunk, BUF_SIZE, 0)ieve content in the given byte range.
 * User is responsible for freeing the memory.
 * 
 * @param host - The host name e.g. www.canterbury.ac.nz
 * @param page - e.g. /index.html
 * @param range - Byte range e.g. 0-500. NOTE: A server may not respect this
 * @param port - e.g. 80
 * @return Buffer - Pointer to a buffer holding response data from query
 *                  NULL is returned on failure.
 */
Buffer *http_query(char *host, char *page, const char *range, int port) 
{
    // struct addrinfo their_addrinfo, *their_addr = NULL;  // connector's and Servers address information   
    struct addrinfo their_addrinfo;
    struct addrinfo *res = NULL;
    int sockfd;
    int byte_count;

    // Allocating space for the port and Buffer in memory
    char *usrPort = (char*)malloc(sizeof(char) * RANGE_LIMIT);
    char *header = malloc(sizeof(char) * (strlen(page) + strlen(host)) + 27);
    Buffer *buffer = (Buffer*)malloc(sizeof(Buffer));
    buffer->data = (char*)malloc(sizeof(char) * (BUF_SIZE + 27));  // 27 for the header
    buffer->length = 0;

    // printf("%ld\n", sizeof(buffer->data));
    // printf("%ld\n", sizeof(char) * BUF_SIZE);

    // printf("%ld\n", sizeof(char) * (strlen(page) + strlen(host))+27);

    // // Display error if port isnt within bounds
    // // Make a string out of the port number
    int n = snprintf(usrPort, RANGE_LIMIT, "%d", port);  
    if ((n < 0 ) || (n > RANGE_LIMIT)) {
        printf("ERROR: Malformed Port\n");
        exit(EXIT_FAILURE);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, STDIN_FILENO);
    //get host info, make socket and connect it
    memset(&their_addrinfo, 0, sizeof(their_addrinfo));
    their_addrinfo.ai_family = AF_INET;
    their_addrinfo.ai_socktype = SOCK_STREAM;
    sprintf(usrPort, "%d", port);  // change port to a string     
    getaddrinfo(host, usrPort, &their_addrinfo, &res);
    // Connect to the server/host;
    int rc = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (rc == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    sprintf(header, "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", page, host);

    // send(sockfd, header, strlen(header), 0);

    int numbytes = 0;

    //all right ! now that we're connected, we can receive some data!
    // byte_count = recv(sockfd, (void*)buffer->data, 1030, 0); // <-- -1 to leave room for a null terminator
    // buffer->data[byte_count] = 0; // <-- add the null terminator
    // printf("%d\n", byte_count);

    // buffer->data = realloc((void*)buffer->data, BUF_SIZE+100000000);
    // numbytes = read(sockfd, (void*)buffer->data, BUF_SIZE+10000);
    // printf("%d\n", numbytes);
    // numbytes = read(sockfd, (void*)&buffer->data[numbytes], BUF_SIZE+10000);
    // printf("%d\n", numbytes);
    // numbytes = read(sockfd, (void*)&buffer->data[numbytes], BUF_SIZE+10000);
    // printf("%d\n", numbytes);
    // numbytes = read(sockfd, (void*)&buffer->data[numbytes], BUF_SIZE+10000);
    // printf("%d\n", numbytes);
    // numbytes = read(sockfd, (void*)&buffer->data[numbytes], BUF_SIZE+10000);
    // printf("%d\n", numbytes);
    // size_t bytes = 0;

    // while((bytes = read(sockfd, (void*)&buffer->data[bytes], BUF_SIZE+100000000)) > 0) {
    //   buffer->length += bytes;
    // }
    size_t bytes = 0;
    size_t buffData = 0;
    size_t a = 1000000;
    bool reset = false;

    write(sockfd, header, strlen(header));
    bytes = read(sockfd, (void*)buffer->data, BUF_SIZE);

    do {
        // if (reset) buffer->data = realloc((void*)buffer->data, BUF_SIZE);
        // buffer->data = realloc((void*)buffer->data, buffData);
        append_buffer(buffer, bytes);
        printf("%ld\n", buffer->length);
        bytes = read(sockfd, (void*)&buffer->data[buffer->length], BUF_SIZE);
        // buffData += BUF_SIZE + 27;
        // reset = true;
    } while (bytes > 0);

	// int size_recv = 0;
    // int total_size = 0;
    // // char chunk[1600];
    // char *buff[500];

    // do {
    //     size_recv = read(sockfd, (void*)buffer->data, BUF_SIZE);;
    //     // memcpy(buff, buffer->data, BUF_SIZE);
    
    //     buffer->data = realloc((void*)buffer->data, BUF_SIZE+105);
    //     // size_recv = read(sockfd, (void*)&buffer->data[size_recv], 105);
    //     size_recv = read(sockfd, (void*)&buffer->data[size_recv], 105);
    //     // total_size += size_recv;
    //     // printf("recv  %d\n", total_size);
    //     printf("recv  %d\n",  size_recv);
    // } while (size_recv == BUF_SIZE);


    // buffer->data = realloc((void*)buffer->data, BUF_SIZE+200);
    // memset((void*)buffer->data, 0, 500);
    // // buffer->data = realloc((void*)buffer->data, BUF_SIZE+200);
    // size_recv = read(sockfd, (void*)buffer->data, BUF_SIZE+200);

    // } while(size_recv == BUF_SIZE);

    // memcpy((void*)buffer->data, chunk, 1448);

    // do {
    //     // write and read from server
    //     write(sockfd, header, strlen(header));

    //     buffer->data = (char*)realloc(buffer->data, 3000);

    //     // memcpy(buffer->data + buffer->length, buffer->data, 1000);

	//     // buffer->length += bytes;

    //     printf("%ld\n", sizeof(buffer->data));
    //     numbytes = read(sockfd, (void*)buffer->data, bytes);

    //     buffer->data[numbytes] = 0;
    //     bytes += BUF_SIZE;

    // } while (numbytes > 0);
    free(usrPort);
    free(header);
    close(sockfd);


    // char *store = malloc(sizeof(char) *  + 1);
    // char *message1 = "Hello";
    // char *message2 = " Jonathan";

    // char *name = malloc(sizeof(char) * strlen(message1));  // initial

    // memcpy(name, message1, 5);  // copy the first message
    // name = realloc(name, sizeof(char) * 14);
    // memcpy(&name[5], message2, 9);  // concaternate the second message with the first

    // puts(name);

    return buffer;
}




/**
 * Separate the content from the header of an http request.
 * NOTE: returned string is an offset into the response, so
 * should not be freed by the user. Do not copy the data.
 * @param response - Buffer containing the HTTP response to separate 
 *                   content from
 * @return string response or NULL on failure (buffer is not HTTP response)
 */
char* http_get_content(Buffer *response) {

    char* header_end = strstr(response->data, "\r\n\r\n");

    if (header_end) {
        return header_end + 4;
    }
    else {
        return response->data;
    }
}


/**
 * Splits an HTTP url into host, page. On success, calls http_query
 * to execute the query against the url. 
 * @param url - Webpage url e.g. learn.canterbury.ac.nz/profile
 * @param range - The desired byte range of data to retrieve from the page
 * @return Buffer pointer holding raw string data or NULL on failure
 */
Buffer *http_url(const char *url, const char *range) {
    char host[BUF_SIZE];
    strncpy(host, url, BUF_SIZE);

    char *page = strstr(host, "/");
    
    if (page) {
        page[0] = '\0';

        ++page;
        return http_query(host, page, range, 80);
    }
    else {  // char *header = 0;

        fprintf(stderr, "could not split url into host/page %s\n", url);
        return NULL;
    }
}


/**
 * Makes a HEAD request to a given URL and gets the content length
 * Then determines max_chunk_size and number of split downloads needed
 * @param url   The URL of the resource to download
 * @param threads   The number of threads to be used for the download
 * @return int  The number of downloads needed satisfying max_chunk_size
 *              to download the resource
 */
int get_num_tasks(char *url, int threads) {
   assert(0 && "not implemented yet!");
}


int get_max_chunk_size() {
    return max_chunk_size;
}
