global  isr0,isr1,isr2,isr3,isr4,isr5,isr6,isr7,isr8,isr9,isr10,isr11,isr12,isr13,isr14,isr15
global  isr16,isr17,isr18,isr19,isr20,isr21,isr22,isr23,isr24,isr25,isr26,isr27,isr28,isr29,isr30,isr31

;0 Division By Zero
isr0:
  cli
  push byte 0
  push byte 0
  jmp isr_common_stub
  
;Debug Exception
isr1:
  cli
  push byte 0
  push byte 1
  jmp isr_common_stub

;Non Maskable Interrupt Exception
isr2:
  cli
  push byte 0
  push byte 2
  jmp isr_common_stub
  
;Breakpoint Exception
isr3:
  cli
  push byte 0
  push byte 3
  jmp isr_common_stub
 
;Into Dected Overflow Exception 
isr4:
  cli
  push byte 0
  push byte 4
  jmp isr_common_stub

;Out of Bounds Exception
isr5:
  cli
  push byte 0
  push byte 5
  jmp isr_common_stub
  
;Invalid Opcode Exception
isr6:
  cli
  push byte 0
  push byte 6
  jmp isr_common_stub
  
;No Coprocessor Exception
isr7:
  cli
  push byte 0
  push byte 7
  jmp isr_common_stub
  
  
;Double Fault Exception
isr8:
  cli
  push byte 8;
  jmp isr_common_stub
  
 ;Coprocessor Segment Overrun Exception
isr9:
  cli
  push byte 0
  push byte 9
  jmp isr_common_stub 
  
;Bad TSS Exception
isr10:
  cli
  push byte 10;
  jmp isr_common_stub
  
;Segment Not Present Exception
isr11:
  cli
  push byte 11;
  jmp isr_common_stub

;Stack Fault Exception
isr12:
  cli
  push byte 12;
  jmp isr_common_stub
  
;General Protection Fault
isr13:
  cli
  push byte 13;
  jmp isr_common_stub

;Page Fault Exception
isr14:
  cli
  push byte 14;
  jmp isr_common_stub
  
;Unknown Interrupt Exception
isr15:
  cli
  push byte 0
  push byte 15
  jmp isr_common_stub
  
;Coprocessor Fault Exception
isr16:
  cli
  push byte 0
  push byte 16
  jmp isr_common_stub

;Alignment Check Exception (486+)
isr17:
  cli
  push byte 0
  push byte 17
  jmp isr_common_stub
  
;Machine Check Exception (Pentium/586+)
isr18:
  cli
  push byte 0
  push byte 18
  jmp isr_common_stub
  
;19 to 31 Reserved Exception  
isr19:
  cli
  push byte 0
  push byte 19
  jmp isr_common_stub
  
isr20:
  cli
  push byte 0
  push byte 20
  jmp isr_common_stub
  
isr21:
  cli
  push byte 0
  push byte 21
  jmp isr_common_stub
  
isr22:
  cli
  push byte 0
  push byte 22
  jmp isr_common_stub
  
isr23:
  cli
  push byte 0
  push byte 23
  jmp isr_common_stub
  
isr24:
  cli
  push byte 0
  push byte 24
  jmp isr_common_stub
  
isr25:
  cli
  push byte 0
  push byte 25
  jmp isr_common_stub
  
isr26:
  cli
  push byte 0
  push byte 26
  jmp isr_common_stub
  
isr27:
  cli
  push byte 0
  push byte 27
  jmp isr_common_stub
  
isr28:
  cli
  push byte 0
  push byte 28
  jmp isr_common_stub
  
isr29:
  cli
  push byte 0
  push byte 29
  jmp isr_common_stub
  
isr30:
  cli
  push byte 0
  push byte 30
  jmp isr_common_stub
  
isr31:
  cli
  push byte 0
  push byte 31
  jmp isr_common_stub

extern isr_fault_handler

isr_common_stub:
  pusha
  push ds
  push es
  push fs
  push gs
  mov ax,0x10
  mov ds,ax
  mov es,ax
  mov fs,ax
  mov gs,ax
  mov eax,esp
  push eax
  mov eax,isr_fault_handler
  call eax ;with this call, preserves the 'eip' register
  pop eax
  pop gs
  pop fs
  pop es
  pop ds
  popa
  add esp,8
  iret
  