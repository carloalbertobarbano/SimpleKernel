#include "stdio.h"

char *videomem = (char*)(0xb8000);
int mem_cursor = 0;
int cursorX = 0;
int cursorY = 0;
int color = 0x07;

const int video_col = 80*2;
const int video_row   = 24;

int getCursorVideomem()
{
	mem_cursor = cursorY*video_col+cursorX;
	return mem_cursor;
}

void scroll()
{
  if(cursorY > video_row)
  {
     int diff = cursorY - video_row;
     int char_diff = diff * video_col;
     
     int i = 0;
     for(i = 0;i < video_row*video_col;i++)
     {
         videomem[i] = videomem[i+char_diff];
     }
    
     int clear_start;
     for(clear_start = i;clear_start < i + char_diff;clear_start++)
     {
	 videomem[clear_start] = 0;     
     }
    cursorY = video_row;    
  }
}

void set_color(int c)
{
  color = c;
}

void clear()
{
   mem_cursor = 0;

   while(videomem[mem_cursor])
   {
      videomem[mem_cursor] = ' ';
      mem_cursor++;
      videomem[mem_cursor] = color;
      mem_cursor++;
   }

   mem_cursor = 0;   
   cursorX = cursorY = 0;
}

void clear_from(int pos)
{
     int i = pos;
     int first_is_char = 0;
     if(i % 2 == 0)first_is_char = 1;
	
     while(videomem[i])
     {
	if(first_is_char == 1)
	{		
           videomem[i] = ' ';
	   i++;
           videomem[i] = color;
           i++;
	} 
	else
	{
           videomem[i] = color;
           i++;	
	   videomem[i] = ' ';
	   i++;
	}
    }
}

void putch(char c)
{
   if(c == '\n')
   {
     cursorY++;
     cursorX = 0;
     return; 
   }
   
   if(c == '\t')
   {
      cursorX += 8;
      return;
   }

   if(c == '\b')
   {
       cursorX--;
       mem_cursor--;
       videomem[mem_cursor] = color;
       cursorX--;
       mem_cursor--;
       videomem[mem_cursor] = 0;	   
       return;	   
   }
   
   if(cursorX >= video_col)
   {
     cursorX = 0;
     cursorY++;
   }

   scroll();

   mem_cursor = cursorY*video_col+cursorX;

   videomem[mem_cursor] = c;
   cursorX++;
   mem_cursor++;
   videomem[mem_cursor] = (char*)color;
   mem_cursor++;
   cursorX++;
}

void puti(int i)
{
   scroll();

   mem_cursor = cursorY*video_col+cursorX;
    
   char number[100];
   char *ptr = &number[0];
	
    ptr = itoa(i,number,10);
	
   print(number);
}

void print(char *msg)
{
  while(*msg)
  {
    putch(*msg);
    msg++;
  }
} 

char *itoa(int value,char *result,int base)
{
	if (base < 2 || base > 36) 
       { 
	        *result = '\0'; 
	       return result; 
	}
	
	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;
	
	do 
	{
	        tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
        }
	while (value);
	
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	
	while(ptr1 < ptr) 
	{
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
  return result;
}