#ifndef STDIO_H
#define STDIO_H

#include "string.h"

#define EOF \0
#define NULL 0
#define null NULL

extern void clear();
extern void clear_from(int pos);

extern void putch(char c);
extern void puti(int i);
extern void print(char *msg);

extern char *itoa(int value,char *result,int base);

extern void set_color(int color);

extern char *videomem;
extern int   getCursorVideomem();

#endif
