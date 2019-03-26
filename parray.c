#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "parray.h"

typedef char byte;

parray_t* parray_new(int size, int count)
{
    int pgsize = 4096;
    struct parray* p = NULL;
    p = malloc(sizeof(struct parray*));
    //calculate the size of the pages
    while ((float)size/pgsize > 1) {
      pgsize = pgsize * 2;
    }
    p->size = size;
    //for each array, there will be count + 2 guard pages, as well as count data pages
    //since counting starts at 0 only add 1 to count instead of 2
    posix_memalign(&p->array, pgsize, pgsize*(count+1+count));
    int j = 1;
    //loop through memory region protecting appropriate pages
    for (int i = 0; i < pgsize*(count+1+count); i = i + pgsize) {
      if ((j % 2) == 0) {
        //printf("Region %d is %p to %p\n", (j/2)-1, p->array + i, p->array + i + pgsize-1);
      }
      else {
        if (mprotect(p->array + i, pgsize, PROT_NONE)) {
              fprintf(stderr,"ERROR WITH MPROTECT\n");
              exit(-1);
        }
        // else {
        //   printf("Region %p to %p is protected\n", p->array + i, p->array + i + pgsize - 1);
        // }
      }
      j = j + 1;
    }
    return p;
}

void* parray_entry(struct parray* p, int index)
{
    int pgsize = 4096;
    while ((float)p->size/pgsize > 1) {
      pgsize = pgsize * 2;
    }
    //start at beginning of array, skip to end of correct region, subtract size to get beginning of data
    byte* entry = p->array + (pgsize * (2+(2*index))) - (p->size);
    //printf("index: %d\nentry: %p\nentry+size: %p\n", index, entry, entry+p->size);
    return entry;
}
