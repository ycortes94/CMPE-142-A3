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

int FIFO(int pages[], int n, int capacity)
{
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

/*FOR LEAST RECENTLY USED ALGORITHM*/
int findLRU(int time[], int n)
{
   int i, minimum = time[0], pos = 0;

   for (i = 1; i < n; ++i)
   {
      if (time[i] < minimum)
      {
         minimum = time[i];
         pos = i;
      }
   }

   return pos;
}

void LRU()
{
   unsigned adr;
   char rw;
   static const char filename[] = "memory.dat";
   FILE *fp = fopen(filename, "r");
   if (fp != NULL)
   {
      while (fscanf(fp, "%x %c", &adr, &rw) != EOF)
      {
         int no_of_frames = 100, no_of_pages = 20, frames[100], pages[20], counter = 0, time[100], flag1, flag2, i, j, pos, faults = 0;
         
         for (i = 0; i < no_of_pages; ++i)
         {
           fscanf(fp, "%x", pages[i]);
         }

         for (i = 0; i < no_of_frames; ++i)
         {
            frames[i] = -1;
         }

         for (i = 0; i < no_of_pages; ++i)
         {
            flag1 = flag2 = 0;

            for (j = 0; j < no_of_frames; ++j)
            {
               if (frames[j] == pages[i])
               {
                  counter++;
                  time[j] = counter;
                  flag1 = flag2 = 1;
                  break;
               }
            }

            if (flag1 == 0)
            {
               for (j = 0; j < no_of_frames; ++j)
               {
                  if (frames[j] == -1)
                  {
                     counter++;
                     faults++;
                     frames[j] = pages[i];
                     time[j] = counter;
                     flag2 = 1;
                     break;
                  }
               }
            }

            if (flag2 == 0)
            {
               pos = findLRU(time, no_of_frames);
               counter++;
               faults++;
               frames[pos] = pages[i];
               time[pos] = counter;
            }

            printf("\n");

            for (j = 0; j < no_of_frames; ++j)
            {
               printf("%d\t", frames[j]);
            }
         }

         printf("\n\nTotal Page Faults = %d", faults);
         fclose(fp);
      }
   }
   else
   {
      perror(filename);
   }
}

void Random(int frames, char *tracefile, int debug)
{
   unsigned adr;
   char rw;
   unsigned pagenum;
   struct tableentry pt[ptsize];
   struct tableentry cache[frames];

   int foundcache = -1;
   srand(time(NULL));
   int rndm;

   int frontcache = -1;
   int nextavailcache = 0;

   ptInit(pt, ptsize);
   cacheInit(cache, frames);

   FILE *file;
   file = fopen(tracefile, "r");
   if (file)
   {
      while (fscanf(file, "%x %c", &adr, &rw) != EOF)
      {
         pagenum = adr / (16 * 16 * 16);
         if (pt[pagenum].valid == 0)
         {
            pt[pagenum].vpn = pagenum;
            pt[pagenum].valid = 1;
         }
         foundcache = foundincache(cache, frames, pagenum, debug);

         if (foundcache >= 0)
         {
            if (rw == "W")
            {
               cache[foundcache].dirty = 1;
            }
         }
         else if (frontcache == -1)
         {
            if (debug)
            {
               printf("filled in 1st empty of cahce \n");
            }
            frontcache = 0;
            nextavailcache = 1;
            cache[frontcache].vpn = pagenum;
            pt[pagenum].present = 1;
            readcnt++;
            if (rw == "W")
            {
               cache[frontcache].dirty = 1;
            }
         }
         else if (frontcache == nextavailcache)
         {
            if (debug)
            {
               printf("cache is full \n");
            }
            rndm = rand() % frames;
            if (cache[rndm].dirty == 1)
            {
               pt[cache[rndm].vpn].present = 0;
               if (debug)
               {
                  printf("write to disk \n");
               }
               writecnt++;
            }
            if (debug)
            {
               printf("read to disk \n");
            }
            pt[pagenum].present = 1;
            readcnt++;
            cache[rndm] = pt[pagenum];
            if (rw == "W")
            {
               cache[rndm].dirty = 1;
            }
            else
            {
               cache[rndm].dirty = 0;
            }
         }
         else
         {
            if (debug)
            {
               printf("slot %d in array is filled \n", nextavailcache);
            }
            cache[nextavailcache].vpn = pagenum;
            if (debug)
            {
               printf("read from disk \n");
            }
            readcnt++;
            pt[pagenum].present = 1;
            if (rw == "W")
            {
               cache[nextavailcache].dirty = 1;
            }
            nextavailcache = (nextavailcache + 1) % frames;
         }
         traceEv++;
         foundcache = -1;
         if (debug)
         {
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
      int frame, debug;
      char *tfile;
      FIFO();
      LRU();
      Random(frame, tfile, debug);
      fclose(fp);
   }
   else
   {
      perror(filename);
   }
   return 0;
}
