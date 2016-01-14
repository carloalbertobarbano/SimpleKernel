#include "system.h"
#include "stdio.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "timer.h"
#include "keymap.h"

int cursor_shown = 0;

void timer(struct regs *s);
void keyboard_handler(struct regs *s);

void kmain(void *mdb,unsigned int magic)
{
   set_color(0x17);
   clear();

   if(magic != 0x2BADB002)
   {
      set_color(0x14);
      print("Cosmos: Error initializing kernel: address not 0x2BADB002!");
   }
   else
   {
      set_color(0x17);

      print("Cosmos: Starting in protected mode.. \n");
      print("Cosmos: Loading Kernel.. \n");
     
      gdt_install();
      idt_install();
      irq_install();
      __asm__ __volatile__("sti");
	   
      timer_install(timer);
	
      irq_install_handler(1,keyboard_handler);
	   
      print("Cosmos: Kernel Loaded. \n");
      print("Cosmos: System ready for input. Welcome, User\n");
      print("cosmos@os > ");
   }

   
   for(;;)
   {
        timer_wait(1);	   
   }	   //Infinite loop
     
}

void timer(struct regs *s)
{
	timer_ticks++;
	
	// % 18 Is a second!!
	
	if(timer_ticks % 10 == 0)
	{
		if(cursor_shown == 0)
		{
			
			int i = getCursorVideomem();
			videomem[i+2] = '_';
			videomem[i+3] = 0x17;
			clear_from(i+4);
			cursor_shown = 1;
		}
		else
		{
			int i = getCursorVideomem();
			clear_from(i+1);
			cursor_shown = 0;
		}
	}
}


void keyboard_handler(struct regs *r)
{
	unsigned char scancode = inportb(0x60);
	
	if(scancode & 0x80) //Release
	{
		
	}
	else
	{
		putch(kbdus[scancode]);
	}

        if(scancode == '\n')
        {
           print("cosmos@os > ");
        }
}
