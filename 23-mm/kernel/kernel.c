#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../drivers/keyboard.h"
#include "../mm/mm.h"
#include "../libc/string.h"
void kernel_main() {

  u32 total;
    clear_screen();
    irq_install();

      mm_init( &memman); 
      mm_free(&memman,FREE_MEM_START_ADDR,FREE_MEM_END_ADDR-FREE_MEM_START_ADDR);

        total = mm_total(&memman);
        char total_memory_str[16] = "";
        hex_to_ascii(total, total_memory_str);
        kprint("Total memory: ");
        kprint(total_memory_str);
        kprint("\n");

        
     kprint("Type something, it will go through the kernel\n"
        "Type END to halt the CPU\n> ");

    
    
}
