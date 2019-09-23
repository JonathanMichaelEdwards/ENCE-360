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
    int src = open("test/test.dat", O_RDONLY);
    if (src == -1) handle_error("fstat");

    int dst = open("test/output.dat", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dst == -1) handle_error("open");

    // get the file size  
    size_t size = file_size(src);
    
    
    char *buffer = malloc(size);
    

    /*
    * TODO: copy the file using read/write
    * 
    */
   ////
   ssize_t fileread = read(src, buffer, size);
   write(dst, buffer, fileread);
   ////
    
    close(src);
    close(dst);
    
    free(buffer);
    
    exit(EXIT_SUCCESS);
}