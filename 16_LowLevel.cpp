#include "16_LowLevel.h"
#include <stdlib.h>     /* malloc, free, rand */


/***********************************************
16.5
************************************************/
int TestMachineEndian(){
  short testData = 0x0001;
  char *byte = (char*) &testData;
  return(byte[0] ? LITTLE_ENDIAN : BIG_ENDIAN);
}


/***********************************************
16.9
************************************************/
void* aligned_malloc(size_t required_bytes, size_t alignment){
  void *p1;   // original block
  void **p2;  // aligned block

  int offset = alignment - 1 + sizeof(void*);

  if((p1 = (void*)malloc(required_bytes + offset)) == NULL){
    return NULL; 
  }
  p2 = (void**)(((size_t)(p1) + offset) & ~(alignment - 1));
  p2[-1] = p1;
  return p2;
}

void aligned_free(void *p){
  free(((void**)p)[-1]);
}


/***********************************************
16.10
************************************************/
int** My2DAlloc(int rows, int cols){
  int header = rows * sizeof(int*);
  int data = rows * cols * sizeof(int);
  int** rowptr = (int**)malloc(header + data);
  int* buf = (int*)(rowptr + rows);
  int k;
  for(k = 0; k < rows; ++k){
    rowptr[k] = buf + k*cols;
  }
  return rowptr;
}


/***********************************************
Chapter16 Completed
************************************************/