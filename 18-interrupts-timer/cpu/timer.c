#include "timer.h"
#include "isr.h"
#include "../drivers/screen.h"

u32 tick = 0;
static timer_callback(registers_t regs){
     tick++;
     if(tick %100 == 0){
        kprint("Tick: ");
        char tick_ascii[256];
        int_to_ascii(tick, tick_ascii);
        kprint(tick_ascii);
        kprint("\n");
     }
 

}

 void init_timer(u32 freq){
     register_interrupt_handler(IRQ0, timer_callback);

     //init pit

     u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
 }
