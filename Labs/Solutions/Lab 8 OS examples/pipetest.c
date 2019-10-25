// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

#define NULL 0


int main(void) {
  int to_child[2];
  int to_parent[2];
 
  char buf[512];
  int n = 0;

  pipe(to_child);
  pipe(to_parent);
  int pid = fork();

  if(pid == 0) {


    close(to_child[1]);
    close(to_parent[0]);
    
    close(0);   
    dup(to_child[0]);
    
    close(1);
    dup(to_parent[1]);    

    char *argv[] = {"wc", NULL};
    exec("wc", argv);
    
  } else { 
   close(to_child[0]); 
   close(to_parent[1]); 
    
   write(to_child[1], "hello world\n", 12);
   close(to_child[1]);


   while((n = read(to_parent[0], buf, 512)) > 0) {
     printf(1, "%s\n", buf);
   }
   
   close(to_parent[0]);
   
   wait();

  }


  exit();
}
