[bits 32]
[extern kernel_main] ; Define calling point. Must have same name as kernel.c 'main' function
global _start
_start:
call kernel_main ; Calls the C function. The linker will know where it is placed in memory
jmp $
