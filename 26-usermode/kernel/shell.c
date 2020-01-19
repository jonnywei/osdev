#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../mm/mm.h"
#include "../fs/initrd.h"
#include "../fs/fs.h"
#include "task.h"

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
        u32 phys_addr = mm_alloc(&memman, 0x100000);
        if(phys_addr == 0){
              kprint("alloc memory error ");
              kprint("\n");
        }else {
            char phys_str[16] = "";
            hex_to_ascii(phys_addr, phys_str);      
            kprint("physical address: ");
            kprint(phys_str);
            kprint("\n");

            memory_set(phys_addr,'x',1000);
            
        }
     
    }else if (strcmp(input, "LS") == 0) {
     int i = 0;
    struct dirent *node = 0;
       while ( (node = readdir_fs(fs_root, i)) != 0)
    {
        kprint("Found file ");
        kprint(node->name);
        fs_node_t *fsnode = finddir_fs(fs_root, node->name);

        if ((fsnode->flags&0x7) == FS_DIRECTORY)
        {
            kprint("\n\t(directory)\n");
        }
        else
        {
            kprint("\n\t contents: \"");
            char buf[256];
            u32 sz = read_fs(fsnode, 0, 256, buf);
            int j;
            for (j = 0; j < sz; j++)
                kprint(buf[j]);
            
            kprint("\"\n");
        }
        i++;
    }
     
    }else if (strcmp(input, "USER") == 0) {
        switch_to_user_mode();
        while(1){
            1+1;
        }
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}