#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "memManagement.h"
#define ptsize 1048567
// using System;
// using System.Collections;
// using System.Collections.Generic;

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

void Random(int frames, char *tracefile, int debug)
{
   unsigned adr;
   char rw;
   unsigned pagenum;
   struct tableentry pt[ptsize];
   struct tableentry cache[frames];

   int foundcache =-1;
   srand(time(NULL));
   int rndm;

   int frontcache =-1;
   int nextavailcache = 0;

   ptInit(pt, ptsize);
   cacheInit(cache, frames);

   FILE* file;
   file = fopen(tracefile, "r");
   if(file){
      while (fscanf(file, "%x %c", &adr, &rw) != EOF){
         pagenum = adr/ (16 * 16 *16);
         if (pt[pagenum].valid ==0){
            pt[pagenum].vpn =pagenum;
            pt[pagenum].valid =1;
         }
         foundcache= foundincache(cache, frames, pagenum, debug);

         if(foundcache >=0){
            if (rw == "W"){
               cache[foundcache].dirty =1;
            }
         }
         else if(frontcache == -1){
            if(debug){
               printf("filled in 1st empty of cahce \n");
            }
            frontcache =0;
            nextavailcache =1;
            cache[frontcache].vpn= pagenum;
            pt[pagenum].present =1;
            readcount++;
            if(rw == "W"){
               cache[frontcache].dirty =1;
            }
         }
         else if (frontcache== nextavailcache){
            if(debug){
               printf("cache is full \n");
            }
            rndm = rand() % frames;
            if(cache[rndm].dirty ==1){
               pt[cache[rndm].vpn].present =0;
               if (debug){
                  printf ("write to disk \n");
               }
               writecnt++;
            }
            if(debug){
               printf ("read to disk \n");
            }
            pt[pagenum].present =1;
            readcnt ++;
            cache[rndm] = pt[pagenum];
            if (rw== "W"){
               cache[rndm].dirty =1;
            }
            else{
               cache[rndm].dirty =0;
            }
         }
         else{
            if(debug){
               printf("slot %d in array is filled \n", nextavailcache);
            }
            cache[nextavailcache].vpn = pagenum;
            if(debug){
               printf("read from disk \n");
            }
            readcnt++;
            pt[pagenum].present =1;
            if(rw== "W"){
               cache[nextavailcache].dirty=1;
            }
            nextavailcache = (nextavailcache +1) % frames;
         }
         traceEv++;
         foundcache =-1;
         if(debug){
            cachedisplay(cache, frames);
         }

      }
      fclose(file);
   }


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

      int frame, debug;
      char *tfile;
      FIFO();
      LRU();
      Random(frame, tfile, debug);
   }
   else
   {
      perror(filename);
   }
   return 0;
}
