#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "parray.h"

// char is confusing for non-strings...
// why not just call it byte?
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
    posix_memalign(&p->array, pgsize, pgsize*(count+2));
    int j = 1;
    //loop through memory region protecting appropriate areas
    for (int i = 0; i < pgsize*(count+2); i = i + pgsize) {
      if ((j % 2) == 0) {
        //printf("Region %p to %p has data\n", p->array + i, p->array + i + pgsize-1);
      }
      else {
        if (mprotect(p->array + i, pgsize, PROT_NONE)) {
              printf("ERROR WITH MPROTECT\n");
        }
        else {
          //printf("Region %p to %p is protected\n", p->array + i, p->array + i + pgsize - 1);
        }
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
    //printf("array start: %p\npagesize: %d\nsize: %d\n", p->array, pgsize, p->size);
    byte* entry = p->array + (pgsize * (2+(2*index))) - (p->size + 1);
    // TODO: compute correct entry
    // |4096| data |4096| data |4096| data |4096
    //0: 2 pages
    //1: 4 pages
    //2: 6 pages
    //pages = 2 + (2*index)
    //printf("index: %d\nentry: %p\nentry+size: %p\n", index, entry, entry+p->size);
    ////printf("entry: %p\n", entry);
    return entry;
}
