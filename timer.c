#include "timer.h"
#include "system.h"


int timer_ticks = 0;

void timer_phase(int hz) 
{
    int divisor = 1193180 / hz;      
    outportb(0x43, 0x36);         
    outportb(0x40, divisor & 0xFF);  
    outportb(0x40, divisor >> 8);     
}

void timer_install(void (*handler)(struct regs *r))
{
    irq_install_handler(0,handler);
}

void timer_uninstall()
{
     irq_uninstall_handler(0);
}

void timer_wait(int ticks)
{
	unsigned long wait_ticks = timer_ticks + ticks;
	
	while(timer_ticks < wait_ticks);
}