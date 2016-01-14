#ifndef IRQ_H
#define IRQ_H

#include "idt.h"

extern void irq_install_handler(int irq,void (*handler)(struct regs *r));
       void irq_unistall_handler(int irq);
extern void irq_remap();
extern void irq_install();

#endif