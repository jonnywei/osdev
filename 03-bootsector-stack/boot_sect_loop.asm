[org 0x7c00]
;tty model
start:
mov ah, 0x0e

mov bp, 0x8000
mov sp, bp
push 'A'
push 'B'
push 'C'


mov al, [0x8000-2]
int 0x10
mov al, [0x8000]
int 0x10



pop bx
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10


mov al, [0x8000-2]
int 0x10


jmp $ ;jump to 当前行，无限循环
; 

the_secret:
    db 'X'

;zero padding and magic bios number
times 510-($-$$) db 0
dw 0xaa55