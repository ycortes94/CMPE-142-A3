#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
   static const char filename[] = "memory.dat";
   FILE *fp = fopen(filename, "r");
   if (fp != NULL)
   {
      
   }
   else
   {
      perror(filename);
   }
   return 0;
}
