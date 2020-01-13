[org 0x7c00]
;tty model
mov bx , HELLO
call print

call print_nl



jmp $ ;jump to 当前行，无限循环


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

HELLO:
    db 'Hello,world!', 0
GOODBYE:
    db 'Goodbye',0    
CR:
    db 0x0a,0x0d,0
   
;zero padding and magic bios number
times 510-($-$$) db 0
dw 0xaa55