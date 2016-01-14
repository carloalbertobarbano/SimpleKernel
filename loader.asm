%include "idt_isr.inc"

global loader
global gdt_flush
global idt_load;
extern gp
extern idtp;
extern kmain

MODULEALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ MODULEALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .text
align 4
MultiBootHeader:
dd MAGIC
dd FLAGS
dd CHECKSUM

STACKSIZE equ 0x4000
loader:
mov esp,stack+STACKSIZE
push eax
push ebx

call kmain

cli

hang:
hlt
jmp hang

gdt_flush:
   lgdt [gp]
   mov ax,0x10
   mov ds,ax
   mov es,ax
   mov fs,ax
   mov gs,ax
   mov ss,ax
   jmp 0x08:flush2
flush2:
   ret

idt_load:
   lidt [idtp]
   ret
    
section .bss
align 4
stack:
resb STACKSIZE
