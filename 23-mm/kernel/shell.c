#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../mm/mm.h"

void user_input(char *input) {

 if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }else if (strcmp(input, "PAGE") == 0) {
        /* Lesson 22: Code to test kmalloc, the rest is unchanged */
        u32 phys_addr;
        u32 page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    }else if (strcmp(input, "MEM") == 0) {
        u32 phys_addr = mm_alloc(&memman, 4);
        if(phys_addr == 0){
              kprint("alloc memory error ");
              kprint("\n");
        }else {
            char phys_str[16] = "";
            hex_to_ascii(phys_addr, phys_str);      
            kprint("physical address: ");
            kprint(phys_str);
            kprint("\n");
        }
     
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}