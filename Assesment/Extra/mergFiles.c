#include <stdio.h>
#include <stdlib.h>
 

// gcc -std=c99 -Wall -g mergFiles.c -o mergFiles && ./mergFiles
int main(int argc, char const *argv[])
{
   FILE *fs1, *fs2, *ft;
 
   char ch;
 
   printf("File 1: %s\n", argv[1]);
   printf("File 2: %s\n", argv[2]);
   printf("Merged File 3: %s\n", argv[3]);

 
   fs1 = fopen(argv[1], "r");
   fs2 = fopen(argv[2], "r");
 
//    if(fs1 == NULL || fs2 == NULL)
//    {
//       perror("Error ");
//       printf("Press any key to exit...\n");
//       exit(EXIT_FAILURE);
//    }
 
   ft = fopen(argv[3], "w"); // Opening in write mode
 
   //    if(ft == NULL)
   //    {
   //       perror("Error ");
   //       printf("Press any key to exit...\n");
   //       exit(EXIT_FAILURE);
   //    }

   while((ch = fgetc(fs1)) != EOF)
      fputc(ch, ft);
 
   while((ch = fgetc(fs2)) != EOF)
      fputc(ch, ft);
 
//    printf("The two files were merged into %s file successfully.\n", file3);
 

   fclose(fs1);
   fclose(fs2);
   fclose(ft);
 

   return EXIT_SUCCESS;
}