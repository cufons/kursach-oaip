

#ifndef UTIL_H_
#define UTIL_H_
#include <stdlib.h>
#include <string.h>
void append(void** ptrr,unsigned &length,unsigned elemsize,const void* elem);
void remove(void** ptrr,unsigned &length,unsigned elemsize,unsigned index);

#endif /* UTIL_H_ */
