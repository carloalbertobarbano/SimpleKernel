#ifndef GDT_H
#define GDT_H

struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;	
} __attribute__((packed));

struct gdt_ptr
{
	unsigned short limit; //Byte dimension of GDT - 1
	unsigned int base;    //Address of GDT
}__attribute__((packed));


extern struct gdt_entry gdt[3];
extern struct gdt_ptr gp;

extern void gdt_flush();      //In loader.asm
extern void gdt_set_gate(int num,unsigned long base,unsigned long limit,unsigned char access,unsigned char granularity);
extern void gdt_install();

#endif
