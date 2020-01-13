switch_to_pm:
    cli

   lgdt[gdt_descriptor]
   
    mov eax ,cr0
    or eax , 0x1
    mov bx, SWITCH_MODE
    call print
    call println
    mov cr0, eax
    jmp CODE_SEG:init_pm

[bits 32]
init_pm: ; we are now using 32-bit instructions
    mov ax,DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax


    mov ebp, 0x90000 ; 6. update the stack right at the top of the free space
    mov esp, ebp

    call BEGIN_PM ; 7. Call a well-known label with useful code

SWITCH_MODE db "Switching",0
SWITCH_MODE1 db "Switching1",0
