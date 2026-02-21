[BITS 16]
[ORG 0]

section .text

global reboot

reboot:
    cli                 

    xor ax, ax
    int 0x19            

.wait_kbc:
    in al, 0x64         
    test al, 0x02       
    jnz .wait_kbc       

    mov al, 0xFE        
    out 0x64, al

.hang:
    hlt                 
    jmp .hang
