/* Title: dup2eg.c
 * Description: ENCE360 Example code - dup2.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) 
{
    int fd;
    
    /* Open my.file */
    if ((fd = open("my2.file", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
        perror("Couldn't open my.file");
        exit(1);
    }

    /* Redirect stdout to my.file */
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("Could not redirect stdin");
        exit(2);
    }

    /* Replace the current process with "ls -l" */
    // /bin/sort // uni computers
    execl("/usr/bin/sort", "-k+7", NULL);   // why does this not work?

    /* If we reach this line, execl must have failed */
    perror("Exec failed");
    exit(3);
}
