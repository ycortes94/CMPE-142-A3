#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
using System;
using System.Collections;
using System.Collections.Generic;

/*
int FIFO(int pages[], int n, int capacity) {
   HashSet<int> s = new HashSet<int>(capacity);
   Queue indexes = new Queue();
   int page_faults = 0;
   for(int i = 0; i < n; i++) {
      if(s.Count < capacity) {
         if(!s.Contains(pages[i])) {
            s.Add(pages[i]);
            page_faults++;
            indexes.Enqueue(pages[i]);
         }
      } else {
         if(!s.Contains(pages[i])) {
            int val = (int)indexes.Peek();
            indexes.Dequeue();
            s.Removal(val);
            s.Add(pages[i]);
            indexes.Enqueue(pages[i]);
            page_faults++;
         }
      }
   }
return page_faults;
}
*/
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