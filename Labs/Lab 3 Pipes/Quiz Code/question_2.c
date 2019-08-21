/* Title: waiting.c
 * Description: ENCE360 Example code - Signals.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>  /* defines pid_t */
#include <unistd.h>     /* defines fork() */
#include <sys/wait.h>   /* defines the wait() system call. */
#include <signal.h>



 /* Function prototypes */
void sigKill();
void install_handler();


int count = 0;

int main(int argc, const char * argv[]) {
    /* storage place for the pid of the child process, and its exit status. */
    pid_t child_pid = 0;
    int child_status = 0;

    /* fork a child process... */
    child_pid = fork();

    printf("child_pid is %i\n", child_pid);

    if (child_pid < 0) { /* fork() and check if there were errors */
        perror("fork"); /* print a system-defined error message */
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) { /* Child code */  
        install_handler();
        signal(SIGKILL, sigKill);
        for (; ; sleep(1)); /*loop forever*/

    } else { /* Parent code */
        printf("Parent processing starts\n");
        
        printf("\nPARENT: sending SIGQUIT\n");
        kill(child_pid, SIGQUIT);
        sleep(1);

        printf("\nPARENT: sending SIGQUIT\n");
        kill(child_pid, SIGQUIT);
        wait(&child_status);
        
        printf("\nFINISHED PROCESS...\n\n");
        sleep(3);
    }

    return EXIT_SUCCESS;
}


void sigQuit()
{
    write(1, "SIGQUIT\n", 8);

    if (count == 0) count++;
    else if (count == 1) exit(0);
}


void install_handler() 
{
    signal(SIGQUIT, sigQuit);  // listener
}
