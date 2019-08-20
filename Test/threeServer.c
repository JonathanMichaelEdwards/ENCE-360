#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include <errno.h>
#include <unistd.h>

#define MAXDATASIZE 1024  


int main(int argc, char *argv[])  {

	if (argc != 2) {  
		fprintf(stderr,"usage: threeServer port-number\n"); 
		exit(1); 
	} 

	// place your code between the lines of //
	///////////////////////////////////////////////////////
    int s = socket(AF_INET, SOCK_STREAM, 0);               // Create Socket

	///////////////////////////////////////////////////////

	struct sockaddr_in sa, caller;
	sa.sin_family = AF_INET;          
	sa.sin_addr.s_addr = INADDR_ANY; 
	sa.sin_port = htons(atoi(argv[1])); 

	// place your code between the lines of //
	///////////////////////////////////////////////////////
    int rc = bind(s, (struct sockaddr *)&sa, sizeof(sa));  // Bind address to socket
    if (rc == -1) { // Check for errors
        perror("bind");
        exit(1);
    }

	//////////////////////////////////////////////////////

	// place your code between the lines of //
	///////////////////////////////////////////////////////
    rc = listen(s, 5);                                     // Listen for connection
    if (rc == -1) { // Check for errors
        perror("listen");
        exit(1);
    }

	///////////////////////////////////////////////////////

	socklen_t length = sizeof(caller);
	// place your code between the lines of //
	////////////////////////////////////////////////////////////
    int msgsock = accept(s, (struct sockaddr*)&caller, &length);

	/////////////////////////////////////////////////////////////

	char message[MAXDATASIZE] = "congrats you successfully connected to the server!";

	while (strlen(message) > 0)
	{
		int numbytes; // number of bytes of data read from socket

		// send data to the client and then get data back from the client:
		// place your code between the lines of //
		///////////////////////////////////////////////////////
        printf("read a message %d bytes: %s\n", numbytes, message);

        write(msgsock, message, numbytes);
        numbytes = read(msgsock, message, MAXDATASIZE - 1);

		///////////////////////////////////////////////////////

		message[numbytes - 1] = '\0';
	}

	// place your code between the lines of //
	///////////////////////////////////////////////////////
    // close the socket
    close(msgsock);
    close(s);

	///////////////////////////////////////////////////////

	exit (0);
}
