org 100h

start:
    mov ax, 5300h
    int 15h
    jc no_apm

    mov ax, 5301h
    int 15h
    jc no_apm

    mov ax, 5308h
    mov bx, 0001h
    mov cx, 0001h
    int 15h

    mov ax, 5307h
    mov bx, 0001h
    mov cx, 0003h
    int 15h

no_apm:
    mov ah, 0Eh
    mov al, 'X'
    int 10h

    jmp $