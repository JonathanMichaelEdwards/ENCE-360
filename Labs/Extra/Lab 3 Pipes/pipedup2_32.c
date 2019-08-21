/* Title: pipedup2.c
 * Description: ENCE360 Example code - dup2.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define INP 1
#define OUTP 0

int main(void) {
    int fd[2];
    pid_t childpid;

    // sort before head
    pipe(fd);
    if ((childpid = fork()) == 0) { /* Child and Grandchild code */
        dup2(fd[INP], STDOUT_FILENO);
        close(fd[OUTP]);
        close(fd[INP]);
        execl("/usr/bin/sort", "sort", NULL);
        perror("The exec of ls failed");
    } else { /* Parent code: Runs head -5 */
        dup2(fd[OUTP], STDIN_FILENO);
        close(fd[OUTP]);
        close(fd[INP]);
        execl("/usr/bin/head", "head", "-2", NULL);
        perror("The exec of sort failed");
    }

    exit(0);
}
