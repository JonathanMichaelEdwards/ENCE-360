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
    int fd = open("dupP.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(fd, 1);
    write(fd, "jake", 5);

    exit(0);
}
