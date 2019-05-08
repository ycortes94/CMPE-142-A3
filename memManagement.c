#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>

void FIFO()
{
    // comments
}

void LRU()
{
   
}

void Random()
{


}

int main(int argc, char **argv)
{
   static const char filename[] = "memory.dat";
   FILE *fp = fopen(filename, "r");
   if (fp != NULL)
   {
      char ch='b';
     //ACTION table
     switch (ch)
     {
         case 'C':
            printf("Process is Created");
            break;
         case 'T':
            printf("Process is Terminated");
            break;
         case 'A':
            printf("Process allocated memory at address 'PAGE'");
            break;
         case 'R':
            printf("Process is read");
            break;
         case 'W':
            printf("Process wrote to 'PAGE'");
            break;
         case 'F':
            printf("Process freed memory at address 'PAGE'");
            break;
         default:
            printf("Default ");
    }

      FIFO();
      LRU();
      Random();
   }
   else
   {
      perror(filename);
   }
   return 0;
}