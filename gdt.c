#include "gdt.h"
#include "stdio.h"

struct gdt_entry gdt[3];
struct gdt_ptr gp;

void gdt_set_gate(int num,unsigned long base,unsigned long limit,unsigned char access,unsigned char granularity)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (granularity & 0xF0);
    gdt[num].access = access;

    print("Cosmos: Installing GDT ");
    puti(num);
    putch('\n');
}

void gdt_install()
{
 
   gdt_set_gate(0,0,0,0,0); //NULL descriptor
   gdt_set_gate(1,0,0xFFFFFFFF,0x9A,0xCF); //Code segment
   gdt_set_gate(2,0,0xFFFFFFFF,0x92,0xCF);
   
   print("Cosmos: Constructing gdt pointer..\n");

   gp.limit = (sizeof(struct gdt_entry) * 3)-1;
   gp.base = &gdt;
   
   print("Cosmos: Setting address for gdt\n");
   gdt_flush();
}
