#include "task.h"
#include "../mm/mm.h"


extern int read_eip();


volatile task_t * current_task;

volatile task_t * ready_queue;

u32 next_pid  =1;

void init_tasking(){

    asm volatile("cli");

    current_task = ready_queue = (task_t*) mm_alloc(&memman, sizeof(task_t));

    current_task-> id = next_pid ++;

   current_task->esp = current_task->ebp = 0;
   current_task->eip = 0;
   current_task->next = 0;

    asm volatile("sti");

}


void task_switch();

int fork(){
    asm volatile("cli");


// Take a pointer to this process' task struct for later reference.
    task_t *parent_task = (task_t*)current_task;



    task_t* new_task = (task_t*) mm_alloc(&memman, sizeof(task_t));

   new_task->id = next_pid++;
   new_task->esp = new_task->ebp = 0;
   new_task->eip = 0;
   new_task->next = 0;

    // add to read queue
    task_t * tmp_task = (task_t *) ready_queue;

    while(tmp_task->next){
        tmp_task = tmp_task->next;
    }
    tmp_task->next = new_task;


    u32 eip = read_eip();


    
    // We could be the parent or the child here - check.
    if (current_task == parent_task)
    {
        // We are the parent, so set up the esp/ebp/eip for our child.
        u32 esp; asm volatile("mov %%esp, %0" : "=r"(esp));
        u32 ebp; asm volatile("mov %%ebp, %0" : "=r"(ebp));
        new_task->esp = esp;
        new_task->ebp = ebp;
        new_task->eip = eip;
        asm volatile("sti");
        return new_task->id;
    }
    else
    {
        // We are the child.
        return 0;
    }


    asm volatile("sti");




}

int getpid(){
    return current_task->id;
}


