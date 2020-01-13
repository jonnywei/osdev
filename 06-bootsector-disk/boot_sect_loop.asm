[org 0x7c00]
;tty model
mov bp, 0x8000
mov sp, bp

mov bx,0x9000
mov dh, 2

call disk_load

mov dx, [0x9000] ; retrieve the first loaded word, 0xdada
    call print


loop:
    jmp $ ;jump to 当前行，无限循环
 


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
    call print_nl
    jmp loop   
sectors_error:
    mov bx, SECTORS_ERROR 
    call print
    call print_nl
    jmp loop 

;function print
print:
    pusha
start:
    mov al, [bx]
    cmp al, 0
    je done

    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp start
done:
    popa
    ret    
; 

print_nl:
    pusha
    mov bx, CR
    call print
    popa
    ret

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Sector error",0
GOODBYE:
    db 'Goodbye',0    
CR:
    db 0x0a,0x0d,0


;zero padding and magic bios number
times 510-($-$$) db 0
dw 0xaa55

times 256 dw 0xdada;
times 256 dw 0xface;

