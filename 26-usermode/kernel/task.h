#ifndef TASK_H
#define TASK_H

#include "../cpu/types.h"

typedef struct task {

    s32 id;

    u32 esp, ebp;
    u32 eip;
    struct task * next;

}task_t;


void init_tasking();


void task_switch();

int fork();

int getpid();

void switch_to_user_mode();
#endif