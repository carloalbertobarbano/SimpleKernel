#include "system.h"

unsigned char inportb(unsigned int port) 
{
	unsigned char ret;
	asm volatile ("inb %%dx,%%al":"=a"(ret):"d"(port));
	return ret;
}

void outportb(unsigned int port,unsigned char value) 
{
	__asm__ __volatile__("outb %%al,%%dx": :"d"(port),"a"(value));
}