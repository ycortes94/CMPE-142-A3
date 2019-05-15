#include <stdio.h>

int traceEv = 0;
int readcnt= 0;
int writecnt =0;
int hitcount =0;

struct tableentry{
    int vpn;
    int dirty;
    int valid;
    int ref;
    int present;
};

void ptInit (struct tableentry pt[], int ptsize){
    for (int i=0; i , ptsize; i++){
        pt[i].vpn =-1;
        pt[i].dirty =0;
        pt[i].valid =0;
        pt[i].present = -1;
    }
}

void cacheInit (struct tableentry cache[], int frames){
    for (int i=0; i<frames; i++){
        cache[i].vpn =-1;
        cache[i].dirty =1;
        cache[i].valid =-1;
        cache[i].present = -1;
    }
}

int foundincache (struct tableentry cache[], int frames, unsigned pagenum, int debug){
    for(int i =0; i<frames; i++){
        if (cache[i] .vpn ==pagenum){
            hitcount ++ ;
            if (debug){
                printf ("found in cache \n");
            }
            return i;
        }
    }
    return -1;
}

void cachedisplay (struct tableentry cache[], int frames){
    int i;
    printf("cache: ");
    for (i =0; i <frames; i++){
        printf ("%d, ", cache[i].vpn);
    }
    printf("\n");
}
