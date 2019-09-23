#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

size_t file_size(int fd) {
  struct stat sb;  
  if (fstat(fd, &sb) == -1) handle_error("fstat");
  
  return  sb.st_size;
}


int main(int argc, char *argv[])
{
    FILE *src = fopen("test/test.dat", "r");
    if (src == NULL) {
        fprintf(stderr, "error opening test.dat");
        exit(EXIT_FAILURE);
    }

    FILE *dst = fopen("test/output.dat", "w");
    if (dst == NULL) {
        fprintf(stderr, "error opening output.dat");
        exit(EXIT_FAILURE);
    }
    
    ////
    size_t size = file_size(fileno(src));  // File -> fd
    char *buffer = malloc(size);
    
    size_t fileread = fread(buffer, size, 1, src);
    fwrite(buffer, size, 1, dst);
    ////
    
    fclose(src);
    fclose(dst);
    
    free(buffer);
    
    exit(EXIT_SUCCESS);
}