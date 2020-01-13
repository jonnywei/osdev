;tty model
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
jmp $ ;jump to 当前行，无限循环
; 
times 510-($-$$) db 0
dw 0xaa55