#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "http.h"


#define HANDLE_ERROR(msg) \
        do { puts("Error: "msg); exit(EXIT_FAILURE); } while(0)


#define EMPTY_HEADER_SIZE 100
#define BUF_SIZE 1024


int t1 = 0;

char *formatHeader(char *host, char *page, const char *range)
{
    char *header = (char*)malloc(sizeof(char) * (strlen(page) + strlen(host)) + EMPTY_HEADER_SIZE);

    // Formatting the header
    if (!t1) {
        if (!strcmp(range, "")) {
            sprintf(header, "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: getter\r\n\r\n", page, host);
        } else {
            sprintf(header, "GET /%s HTTP/1.0\r\nHost: %s\r\nRange: bytes=%s\r\nUser-Agent: getter\r\n\r\n", page, host, range);
        }
    } else {
        sprintf(header, "HEAD /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: getter\r\n\r\n", page, host);
    }

    return header;
}


/**
 * Read N bytes from the FD (File directory) into a Buffer until the number of bytes 
 * isn't greater then 0.
 * Algorithm:
 * - Store the byte info read from FD into a data buffer located at the new buffers
 *   length and check that the number of bytes is greater then 0.
 * - If it is, increase the buffers length by the number of bytes read from FD.
 * - Then Dynamically resize the Buffers data byte size to have a new size of 
 *   exactly the length of the buffer + BUF_SIZE.
 * - Keep looping until the number of bytes read from FD isn't greater then 0.
 * 
 * @param sockfd - Information about the host is stored in a file descriptor
 * @param Buffer - Pointer to buffer holding response data and it's length
 */
void readBytes(int sockfd, Buffer *buffer)
{
    size_t bytes = 0;

    while ((bytes = read(sockfd, (void*)&buffer->data[buffer->length], BUF_SIZE)) > 0) {
        buffer->length += bytes;
        buffer->data = realloc(buffer->data, (buffer->length+BUF_SIZE));
    }
}


/**
 * Close the socket and free memory.
 */
void clear(int sockfd, char *usrPort, char *header, struct addrinfo *addr)
{
    
    free(usrPort);
    free(header);
    freeaddrinfo(addr);
    close(sockfd);
}


/**
 * Perform an HTTP 1.0 query to a given host and page and port number.
 * host is a hostname and page is a path on the remote server. The query
 * will attempt to retrrecv(s, chunk, BUF_SIZE, 0)ieve content in the given byte range.
 * User is responsible for freeing the memory.
 * 
 * @param host  - The host name e.g. www.canterbury.ac.nz
 * @param page  - e.g. /index.html
 * @param range - Byte range e.g. 0-500. NOTE: A server may not respect this
 * @param port  - e.g. 80
 * @return Buffer - Pointer to a buffer holding response data from query
 *                  NULL is returned on failure.
 */
Buffer *http_query(char *host, char *page, const char *range, int port) 
{
    // Initialize Connector's and Server's address info   
    struct addrinfo addrInfo = {0};
    struct addrinfo *addr = NULL;

    // Dynamically allocating memory space 
    char *usrPort = (char*)malloc(sizeof(char) * 2 + 1);
    Buffer *buffer = (Buffer*)malloc(sizeof(Buffer));
    buffer->data = (char*)malloc(sizeof(char) * (BUF_SIZE));
    buffer->length = 0;

    // Format and check conditions
    if (port != 80) HANDLE_ERROR("Port");
    sprintf(usrPort, "%d", port);
    
    
    // Create a socket and get the hosts info
    int sockfd = socket(AF_INET, SOCK_STREAM, STDIN_FILENO);
    if (sockfd == -1) HANDLE_ERROR("Socket");
    addrInfo.ai_family = AF_INET;
    addrInfo.ai_socktype = SOCK_STREAM;
    int ga = getaddrinfo(host, usrPort, &addrInfo, &addr);
    if (ga == -1) HANDLE_ERROR("Connect");

    // Connect to the host;
    int rc = connect(sockfd, addr->ai_addr, addr->ai_addrlen);
    if (rc == -1) HANDLE_ERROR("Connect");

    char *header = formatHeader(host, page, range);
    
    // Write and read N bytes of header data to FD
    write(sockfd, header, strlen(header));
    readBytes(sockfd, buffer);
    clear(sockfd, usrPort, header, addr);  // Close socket and free memory

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
Buffer *http_url(const char *url, const char *range)
{
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
 * @param url       The URL of the resource to download
 * @param threads   The number of threads to be used for the download
 * @return int      The number of downloads needed satisfying max_chunk_size
 *                  to download the resource
 */
int get_num_tasks(char *url, int threads) 
{
    t1 = 1;

    Buffer *buffer = http_url(url, (char*)BUF_SIZE);
    char *rangeBuff = (char*)malloc(sizeof(char) + BUF_SIZE);

    memcpy(rangeBuff, buffer->data, BUF_SIZE);
    char *b = strstr(buffer->data, "Content-Length: ");
    char *c = strtok(b, " ");
    c = strtok(NULL, "\n");
    int byteSize = atoi(c);

    
    if (strstr(rangeBuff, "Accept-Ranges: bytes") != NULL) {
        max_chunk_size = (byteSize / threads);
    } else {
        max_chunk_size = byteSize;
        threads = 1;
    }
    

    t1 = 0;

    free(rangeBuff);
    buffer_free(buffer);

    return threads;
}


int get_max_chunk_size() {
    return max_chunk_size;
}
