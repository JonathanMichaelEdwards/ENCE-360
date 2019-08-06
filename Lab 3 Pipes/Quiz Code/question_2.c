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
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>  /* defines pid_t */
#include <unistd.h>     /* defines fork() */
#include <sys/wait.h>   /* defines the wait() system call. */
#include <signal.h>

int count = 0;

void sigquit()
{
    write(1, "SIGQUIT\n", 8);
    exit(0);
}


void install_handler() 
{
    while (1) {
        if (count == 0) count++;
        else if (count == 1) sigquit();
    }
}
  

int main(int argc, char const *argv[])
{ 

    signal(SIGQUIT, install_handler);

    // char inbuf[] = malloc(sizeof(char) * MSGSIZE); 
    // int fd[2], i; 
  
    // if (pipe(fd) < 0)   // If pipe is less the 0, then fail
    //     exit(1); 
  
    /* write pipe */
    // write(1, "SIGQUIT\n", 8);
   
    

    // for (i = 0; i < 3; i++) { 
    //     /* read pipe */
    //     read(fd[READ], (void*)inbuf, MSGSIZE); 
    //     printf("%s\n", inbuf); 
    // } 


    return EXIT_SUCCESS; 
} 