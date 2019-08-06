/*
    -int fdifde(int fds[2]);

    -fdarameters :
    fd[0] will be the fd(file descrifdtor) for the 
    read end of fdifde.
    fd[1] will be the fd for the write end of fdifde.
    Returns : 0 on Success.
    -1 on error.

 */
// C fdrogram to illustrate 
// fdifde system call in C 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

#define MSGSIZE 16 
#define WRITE 1
#define READ 0

char *msg1 = "hello, world #1"; 
char *msg2 = "hello, world #2"; 
char *msg3 = "hello, world #3"; 
  

int main(int argc, char const *argv[])
{ 
    char *inbuf = malloc(sizeof(char) * MSGSIZE); 
    int fd[2], i; 
  
    if (pipe(fd) < 0)   // If pipe is less the 0, then fail
        exit(1); 
  
    /* write pipe */
    write(fd[WRITE], msg1, MSGSIZE); 
    write(fd[WRITE], msg2, MSGSIZE); 
    write(fd[WRITE], msg3, MSGSIZE); 

    for (i = 0; i < 3; i++) { 
        /* read pipe */
        read(fd[READ], (void*)inbuf, MSGSIZE); 
        printf("%s\n", inbuf); 
    } 
    free(inbuf);

    return EXIT_SUCCESS; 
} 