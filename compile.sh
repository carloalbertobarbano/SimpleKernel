# Kernel Assembly
nasm -f elf -o loader.o  	   loader.asm
nasm -f elf -o idt_isr.o 	   idt_isr.asm
nasm -f elf -o interrupt_request.o interrupt_request.asm

# Kernel C Sources
gcc -c kernel.c system.c stdio.c string.c gdt.c idt.c irq.c timer.c -Wextra -nostdlib -nostartfiles -nodefaultlibs

# Linking
ld -T link.ld -o kernel.bin loader.o idt_isr.o interrupt_request.o kernel.o system.o stdio.o string.o gdt.o idt.o irq.o timer.o
