#include "../drivers/ports.h"
void main(){


    /* Screen cursor position: ask VGA control register (0x3d4) for bytes
     * 14 = high byte of cursor and 15 = low byte of cursor. */
     /* Requesting byte 14: high byte of cursor pos */
     port_byte_out(0x3d4,14);
     int position = port_byte_in(0x3d5);    /* Data is returned in VGA data register (0x3d5) */

    position = position << 8; /* high byte */

    port_byte_out(0x3d4, 15); /* requesting low byte */
    position += port_byte_in(0x3d5);


    int offset_from_vga = position * 2;




    char* video_memory = (char *) 0xb8000;

    video_memory[offset_from_vga] = 'X'; 
    video_memory[offset_from_vga+1] = 0x0f; /* White text on black background */
    
}