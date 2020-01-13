#include "../drivers/screen.h"
void main(){
   
    //  char *screen = VIDEO_ADDRESS;
    // int screen_size = MAX_COLS * MAX_ROWS;
    // int i=0;
    // for (i = 0; i < screen_size; i++) {
    //     screen[i*2] = ' ';
    //     screen[i*2+1] = WHITE_ON_BLACK;
    // }


  
 clear_screen();
           kprint("There is a line\nbreak");

    kprint_at("This text spans multiple lines", 75, 10);
    kprint_at("There is a line\nbreak", 0, 20);
    kprint("There is a line\nbreak");
    // kprint_at("What happens when we run out of space?", 45, 24);
    // kprint_at("This text spans multiple lines", 75, 10);
    //     kprint("There is a line\nbreak");

    // kprint_at("What happens when we run out of space?", 45, 24);
    
}