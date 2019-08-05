/* Title: pipe.c
 * Description: ENCE360 Example code - Pipes
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int parent_to_child[2];
int child_to_parent[2];
static char message[BUFSIZ];
int child_status, size;

#define INP 1
#define OUTP 0

int main(int argc, char *argv[]) {
    char *strMessage = malloc(sizeof(char) * 10);
    int i = 0;


    if (argc != 2) {
        fprintf(stderr, "Usage: %s message\n", argv[0]);
        exit(1);
    }

    /* Create pipes */
    if (pipe(parent_to_child) == -1) {
        perror("Pipe from");
        exit(2);
    }
    if (pipe(child_to_parent) == -1) {
        perror("Pipe - to");
        exit(2);
    }

    switch (fork()) { /* Fork a new process */

    case -1: /* Error forking */
        perror("Fork");
        exit(3);

    case 0: /* Child code */
        close(parent_to_child[INP]);
        close(child_to_parent[OUTP]);

        /* Read from parent */
        if (read(parent_to_child[OUTP], message, BUFSIZ) != -1) {
            while (i < strlen(message)) {
                message[i] = toupper(message[i]);
                // memset(&strMessage[i], message[i], sizeof(char)); // strncat(strMessage, &message[i], 1);
                i++;
            }

            printf("CHILD: Recieved %s\n", message);
        }
        else {
            perror("Read");
            exit(4);
        }

        /* Close pipes */
        close(parent_to_child[OUTP]);
        close(child_to_parent[INP]);
        break;

    default: /* Parent code */
        close(parent_to_child[OUTP]);
        close(child_to_parent[INP]);

        if (write(parent_to_child[INP], argv[1], strlen(argv[1])) != -1) {
            printf("PARENT: Sent %s\n", argv[1]);
        }
        else {
            perror("Write");
            exit(5);
        }
        wait(&child_status);

        /* Close pipes */
        close(parent_to_child[INP]);
        close(child_to_parent[OUTP]);
    }

    return EXIT_SUCCESS;
}
