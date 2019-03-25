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
    struct parray* p = NULL;
    // TODO: Allocate and return parray
    // Add guard pages first at this time
    return p;
}

void* parray_entry(struct parray* p, int index)
{
    int pagesize = getpagesize();
    byte* entry = NULL;
    // TODO: compute correct entry
    
    return entry;
}
