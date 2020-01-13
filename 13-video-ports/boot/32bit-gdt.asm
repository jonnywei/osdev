gdt_start:

gdt_null:
    dd 0x0 ; 4 bytes
    dd 0x0 ; 4 bytes

gdt_code:
    dw 0xffff ; segment length  bits 0-15
    dw 0x0   ; segement base 
    db 0x0    ; segment base 16-23
    db 10011010b ; flags 
    db 11001111b ; flags 2ed
    db 0x0     ;segment base 24-31

gdt_data:
    dw 0xffff ; segment length  bits 0-15
    dw 0x0   ;  segement base 0-15
    db 0x0    ; segment base 16-23
    db 10010010b ; flags 
    db 11001111b ; flags 2ed
    db 0x0     ;segment base 24-31

gdt_end:

gdt_descriptor: ;the CPU can't directly load the GDT address, but it requires a meta structure called the "GDT descriptor" 
                ;with the size (16b) and address (32b) of our actual GDT. It is loaded with the lgdt operation.
    dw gdt_end -gdt_start -1 
    dd gdt_start    


CODE_SEG equ gdt_code - gdt_start
DATA_SEG  equ gdt_data -gdt_start



