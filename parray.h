#ifndef PARRAY_H
#define PARRAY_H 

typedef struct parray 
{
    void* array;
    int size;
} parray_t;

parray_t* parray_new(int size, int count);

void* parray_entry(parray_t* p, int index);


#endif
