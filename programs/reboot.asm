[BITS 16]
[ORG 0]

section .text

global reboot

reboot:
    cli                 ; Interruptları kapat

    ; --------------------------
    ; Method 1: BIOS Bootstrap
    ; --------------------------
    xor ax, ax
    int 0x19            ; BIOS bootstrap loader

    ; Eğer BIOS reset etmezse buraya düşer
    ; --------------------------
    ; Method 2: Keyboard Controller Reset
    ; --------------------------

.wait_kbc:
    in al, 0x64         ; Keyboard controller status
    test al, 0x02       ; Input buffer dolu mu?
    jnz .wait_kbc       ; Doluysa bekle

    mov al, 0xFE        ; CPU reset komutu
    out 0x64, al

.hang:
    hlt                 ; Reset olmazsa burada kal
    jmp .hang
