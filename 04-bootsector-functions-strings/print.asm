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

println:
    pusha
    mov bx, CR
    call print
    popa
    ret
CR:
    db 0x0a,0x0d,0
