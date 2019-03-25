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
    int addr = 0;
    struct parray* p = NULL;
    //calculate the size of the pages
    while ((float)size/pgsize > 1) {
      pgsize = pgsize * 2;
    }
    p->size = size;
    p->array = (void *)malloc(pgsize * (count + 2));
    for (int i = 1; i <= count + 2; i++) {
      if (i % 2 == 0) {

      }
      else {
        if (mprotect(p->array + addr, pgsize, PROT_NONE)) {
          printf("ERROR WITH MPROTECT\n");
        }
      }
      addr = addr + pgsize;
    }
    // TODO: Allocate and return parray
    // Add guard pages first at this time
    return p;
}

// void* parray_entry(struct parray* p, int index)
// {
//     int pagesize = getpagesize();
//     byte* entry = NULL;
//     // TODO: compute correct entry
//
//     return entry;
// }
