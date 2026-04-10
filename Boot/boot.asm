bits 32

%include "Boot/Mboot_desc/mboot.asm"

global _start
extern system_init

section .text
_start:

    cmp eax, 0x2BADB002
    jne hang
    cli
    mov esp, 0x9FC00

    call system_init

hang:
    hlt
    jmp hang