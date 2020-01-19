#ifndef SYSCALL_H
#define SYSCALL_H

#include "../cpu/types.h"
 #include "isr.h"
#include "../drivers/screen.h"

static void* syscalls[1] = {
  &kprint
};
 u32 num_syscalls = 1;


 static void syscall_handler(registers_t *regs);

void init_syscalls(){
    register_interrupt_handler(0x80, &syscall_handler);
}


void syscall_handler(registers_t *regs){

    if(regs->eax >= num_syscalls){
        return;
    }

    void *location = syscalls[regs->eax];
    int ret;


    asm volatile (" \
     push %1; \
     push %2; \
     push %3; \
     push %4; \
     push %5; \
     call *%6; \
     pop %%ebx; \
     pop %%ebx; \
     pop %%ebx; \
     pop %%ebx; \
     pop %%ebx; \
   " : "=a" (ret) : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx), "r" (location));
   regs->eax = ret;

}



int syscall_kprint( char* p1){

    int a;
    int num =0;
    asm volatile ("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1));

    return a;

}

#endif