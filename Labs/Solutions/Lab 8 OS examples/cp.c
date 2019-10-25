#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];



void cat_to(int src_fd, int dest_fd) {
  int n;

  while((n = read(src_fd, buf, sizeof(buf))) > 0)
    write(dest_fd, buf, n);

}

int main(int argc, char *argv[]) {
  int src_fd;
  int dest_fd;

  if(argc != 3){
    printf(1, "usage: cp src_file dest_file\n");
    exit();
  }

  if((src_fd = open(argv[1], 0)) < 0){
    printf(1, "cat: cannot open %s for reading\n", argv[1]);
    exit();
  }

  if((dest_fd = open(argv[2],  O_CREATE | O_RDWR)) < 0){
    printf(1, "cat: cannot open %s for writing\n", argv[2]);
    exit();
  }


  cat_to(src_fd, dest_fd);
  close(src_fd);
  close(dest_fd);

  exit();
}
