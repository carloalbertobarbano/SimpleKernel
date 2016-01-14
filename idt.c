#include "idt.h"
#include "string.h"
#include "stdio.h"

struct idt_entry idt[256];
struct idt_ptr     idtp;

extern void isr0(),isr1(),isr2(),isr3(),isr4(),isr5(),isr6(),isr7(),isr8(),isr9(),isr10();
extern void isr11(),isr12(),isr13(),isr14(),isr15(),isr16(),isr17(),isr18(),isr19(),isr20();
extern void isr21(),isr22(),isr23(),isr24(),isr25(),isr26(),isr27(),isr28(),isr29(),isr30(),isr31();

unsigned char* isr_message[] = 
{
        "Division by Zero",
	"Debug Exception",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS Exception",
	"Segment Not Present",
	"Stack Fault Exception"
	"General Protection Fault",
	"Page Fault Exception",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Aligment Check",
	"Machine Check",
	"Reserved"    //to 31
};

void idt_set_gate(unsigned char num,unsigned long base,unsigned short sel,unsigned char flags)
{
         idt[num].base_lo = (base & 0xFFFF);
         idt[num].base_hi = (base >> 16) & 0xFFFF;

         idt[num].sel = sel;
         idt[num].always0 = 0;
         idt[num].flags = flags;	
}

void isrs_install()
{
	idt_set_gate(0,  (unsigned)isr0,0x08,0x8E);
	idt_set_gate(1,  (unsigned)isr1,0x08,0x8E);
	idt_set_gate(2,  (unsigned)isr2,0x08,0x8E);
	idt_set_gate(3,  (unsigned)isr3,0x08,0x8E);
	idt_set_gate(4,  (unsigned)isr4,0x08,0x8E);
	idt_set_gate(5,  (unsigned)isr5,0x08,0x8E);
	idt_set_gate(6,  (unsigned)isr6,0x08,0x8E);
	idt_set_gate(7,  (unsigned)isr7,0x08,0x8E);
	idt_set_gate(8,  (unsigned)isr8,0x08,0x8E);
	idt_set_gate(9,  (unsigned)isr9,0x08,0x8E);
	idt_set_gate(10,(unsigned)isr10,0x08,0x8E);
	idt_set_gate(11,(unsigned)isr11,0x08,0x8E);
	idt_set_gate(12,(unsigned)isr12,0x08,0x8E);
	idt_set_gate(13,(unsigned)isr13,0x08,0x8E);
	idt_set_gate(14,(unsigned)isr14,0x08,0x8E);
	idt_set_gate(15,(unsigned)isr15,0x08,0x8E);
	idt_set_gate(16,(unsigned)isr16,0x08,0x8E);
	idt_set_gate(17,(unsigned)isr17,0x08,0x8E);
	idt_set_gate(18,(unsigned)isr18,0x08,0x8E);
	idt_set_gate(19,(unsigned)isr19,0x08,0x8E);
	idt_set_gate(20,(unsigned)isr20,0x08,0x8E);
	idt_set_gate(21,(unsigned)isr21,0x08,0x8E);
	idt_set_gate(22,(unsigned)isr22,0x08,0x8E);
	idt_set_gate(23,(unsigned)isr23,0x08,0x8E);
	idt_set_gate(24,(unsigned)isr24,0x08,0x8E);
	idt_set_gate(25,(unsigned)isr25,0x08,0x8E);
	idt_set_gate(26,(unsigned)isr26,0x08,0x8E);
	idt_set_gate(27,(unsigned)isr27,0x08,0x8E);
	idt_set_gate(28,(unsigned)isr28,0x08,0x8E);
	idt_set_gate(29,(unsigned)isr29,0x08,0x8E);
	idt_set_gate(30,(unsigned)isr30,0x08,0x8E);
	idt_set_gate(31,(unsigned)isr31,0x08,0x8E);
}

void idt_install()
{
	print("Cosmos: Constructing IDT pointer..\n");
	
	idtp.limit = (sizeof(struct idt_entry)*256)-1;
	idtp.base = &idt;
	
	print("Cosmos: Initializing Idt/Irsr structures..\n");
	memset(&idt,0,sizeof(struct idt_entry)*256);
	
	isrs_install();
	
	print("Cosmos: Loading isr on kernel..\n");
	
	idt_load();
}

void isr_fault_handler(struct regs *r)
{
        if(r->int_no < 32)
	{
		print("\nException Caught: ");
		if(r->int_no < 19)
			print(isr_message[r->int_no]);
		else
			print(isr_message[19]);
		print("\nSystem Halted!\n");
		
		for(;;);
	}		
}
