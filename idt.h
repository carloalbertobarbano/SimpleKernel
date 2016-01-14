#ifndef IDT_H
#define IDT_H

struct idt_entry
{
	unsigned short base_lo;
	unsigned short sel;
	unsigned char always0;
	unsigned char flags;
	unsigned short base_hi;
}__attribute__((packed));

struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));

struct regs
{
        unsigned int gs,fs,es,ds;
	unsigned int edi,esi,ebp,esp,ebx,edx,ecx,eax;
	unsigned int int_no, err_code;
	unsigned int eip,cs,eflags,useresp,ss;
};

extern struct idt_entry idt[256];
extern struct idt_ptr	   idtp;

extern void idt_load();  //In loader.asm
extern void idt_set_gate(unsigned char num,unsigned long base,unsigned short sel,unsigned char flags);
extern void isrs_install();
extern void idt_install();
extern void isr_fault_handler(struct regs *r);

#endif