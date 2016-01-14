#include "string.h"

void *memset(void *ptr,int val,int size)
{
	int i = 0;
	for(i = 0;i < size;i++)
	{
		*(unsigned char*)ptr++ = val;
	}
	return ptr;
}