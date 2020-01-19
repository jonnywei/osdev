#ifndef SYSCALL_H
#define SYSCALL_H

#include "../cpu/types.h"

void init_syscalls();

int syscall_kprint(int n, char* p1);

#endif