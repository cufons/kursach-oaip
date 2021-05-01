
#include "util.h"

void append(void** ptrr,unsigned &length,unsigned elemsize,const void* elem) {
	length+=1;
	char* newptr = new char[elemsize*length];
	memcpy(newptr,*ptrr,elemsize*(length-1));
	delete[] *ptrr;
	*ptrr = newptr;
	memcpy((char*)*ptrr+(length-1)*elemsize,elem,elemsize);
}

void remove(void** ptrr,unsigned &length,unsigned elemsize,unsigned index) {
	if (index > length-1) return;
	if (length <= 1) {
		delete[] *ptrr;
		length = 0;
		return;
	}
	const unsigned saved_elem_cnt = length-index;
	char* src_addr = (char*)*ptrr + (index+1)*elemsize;
	char* dest_addr = (char*)*ptrr + (index)*elemsize;
	memcpy(dest_addr,src_addr,saved_elem_cnt*elemsize);
	length-=1;
}
