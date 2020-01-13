disk_load:
    pusha
    push dx
    mov ah, 0x02 ; read
    mov al, dh
    mov ch, 0x00; 
    mov dh, 0x00  ;head 0
    mov cl, 0x02  ; second sector
    int 0x13

    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error
    
    popa
    ret

disk_error:
    mov bx, DISK_ERROR 
    call print
    call println
    jmp $   
sectors_error:
    mov bx, SECTORS_ERROR 
    call print
    call println
    jmp $ 

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Sector error",0


