#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


size_t file_size(int fd) {
  struct stat sb;  
  if (fstat(fd, &sb) == -1) perror("fstat");
  
  return  sb.st_size;
}


/*
 * File copying using mmap.
 */
int main(int argc, char *argv[])
{
    // Initializing files to be open and closed
    int src = open("test/test.dat", O_RDONLY);
    size_t size = file_size(src);  // get the file size  
    int dst = open("test/output.dat", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    // Need to truncate the file to the right size or mmap will fail
    if(ftruncate(dst, size)) perror("ftruncate");
    

    // Mapping memory directly to the cpu
    char *srcMap = mmap(NULL, size, PROT_READ, MAP_PRIVATE, src, STDIN_FILENO);
    char *dstMap = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, dst, STDIN_FILENO);

    memcpy(dstMap, srcMap, size);

    munmap(srcMap, size);
    munmap(dstMap, size);

    close(src);
    close(dst);

    exit(EXIT_SUCCESS);
}