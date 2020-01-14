#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../drivers/keyboard.h"

void kernel_main() {

    clear_screen();
    irq_install();
   kprint("Type something, it will go through the kernel\n"
        "Type END to halt the CPU\n> ");
}
