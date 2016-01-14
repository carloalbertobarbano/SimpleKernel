#ifndef TIME_H
#define TIME_H

#include "irq.h"
#include "idt.h"

extern int timer_ticks;

extern void timer_phase(int hz);      //Rate of timer
extern void timer_install(void (*handler)(struct regs *r));
extern void timer_uninstall();
extern void timer_wait(int ticks);

#endif