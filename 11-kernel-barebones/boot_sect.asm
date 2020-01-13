[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl ;copy bios sets the boot drive

mov bp, 0x9000
mov sp,bp
mov bx, MSG_REAL_MODE
call print
call println



call load_kernel
mov bx, MSG_LOAD_KERNEL_OVER
call print
call println
call switch_to_pm 
jmp $


load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call println
    mov bx, KERNEL_OFFSET
    mov dh, 2 
    mov dl,[BOOT_DRIVE]
    call disk_load

   

    ret

%include "../04-bootsector-functions-strings/print.asm"
%include "../06-bootsector-disk/load-disk.asm"
%include "../08-32bit-gdt/32bit-gdt.asm"
%include "../09-32bit-enter/32bit-enter.asm"


[bits 32]
BEGIN_PM:
    mov ebx,MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET
   jmp $


%include "../07-32bit-print/print-string-pm.asm"

;Global variables
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real mode",0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0
MSG_LOAD_KERNEL_OVER db "Loading kernel OVER", 0

MSG_PROT_MODE db "Enter into 32-bit Protected mode",0

times 510-($-$$) db 0
dw 0xaa55
