#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../drivers/keyboard.h"
void kernel_main() {

    clear_screen();
    isr_install();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");

    asm("sti");

        // init_timer(50);
    init_keyboard(0);
}
