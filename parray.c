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
    //printf("size is: %d\n", size);
    int pgsize = 4096;
    int addr = 0;
    struct parray* p = NULL;
    p = malloc(sizeof(struct parray*));
    //calculate the size of the pages
    while ((float)size/pgsize > 1) {
      pgsize = pgsize * 2;
    }
    //printf("pgsize is: %d\n",pgsize);
    //printf("HERE2\n");
    p->size = pgsize;
    //p->array = (void *)malloc(pgsize * (count + 2));
    posix_memalign(&p->array, pgsize, 0);
    p->array = (void *)malloc(pgsize * (count + 2));
    //printf("HERE3\n");
    for (int i = 1; i <= count + 2; i++) {
      if (i % 2 == 0) {
        //printf("Nothing to do\n");
      }
      else {
        //printf("p->array: %p\np->array + addr: %p\n addr: %d\n&p->array + addr: %p\n", p->array, p->array+addr, addr, &p->array + addr);
        if (mprotect(p->array + addr, pgsize, PROT_NONE)) {
          //printf("ERROR WITH MPROTECT\n");
        }
      }
      addr = addr + pgsize;
    }
    // TODO: Allocate and return parray
    // Add guard pages first at this time
    return p;
}

void* parray_entry(struct parray* p, int index)
{
    if (p) {}
    if (index){}
    //int pagesize = getpagesize();
    //printf("pagesize: %d\n", pagesize);
    byte* entry = NULL;
    // TODO: compute correct entry
    entry = p->array + p->size;
    //printf("entry: %p\n", entry);
    entry = entry + (index * p->size);
    //printf("entry: %p\n", entry);


    return entry;
}
