[org 0x7c00]
;tty model
mov ah, 0x0e

mov bx ,0x7c00
mov ds, bx
mov al, [the_secret]
int 0x10


mov al, [es:the_secret]
int 0x10


mov bx ,0x7c00
mov es, bx
mov al, [es:the_secret]
int 0x10


jmp $ ;jump to 当前行，无限循环
 

the_secret:
    db 'X', 0
GOODBYE:
    db 'Goodbye',0    
CR:
    db 0x0a,0x0d,0
   
;zero padding and magic bios number
times 510-($-$$) db 0
dw 0xaa55