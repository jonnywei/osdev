[org 0x7c00]
;tty model
start:
mov ah, 0x0e
mov al, 'H'
int 0x10
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10
mov al, 'l'
int 0x10
mov al, 'o'
int 0x10
mov al, ' '
int 0x10
mov al, 'O'
int 0x10
mov al, 'S'
int 0x10
mov al, '!'
int 0x10
mov al, ' '
int 0x10

mov al, "1"
int 0x10
mov al, the_secret
int 0x10

mov al, "2"
int 0x10
mov al, [the_secret]
int 0x10


mov al, "3"
int 0x10
mov bx ,the_secret
add bx , 0x7c00
mov al, [bx]
int 0x10




jmp $ ;jump to 当前行，无限循环
; 

the_secret:
    db 'X'

;zero padding and magic bios number
times 510-($-$$) db 0
dw 0xaa55