[org 0x7c00] ;set program origin

mov bp, 0x8000 ;set up stack for real-mode
mov sp,bp

mov ah, 0x0e ;set up rolling typing for int 0x10


mov bx, greeting
call f_print
call f_load_kernel
call switch_to_protected_mode
jmp $;Loop in case of faults

[bits 16]
KERNEL_OFFSET equ 0x1000 ;Location of the kernel
f_load_kernel:
    mov bx, kernel_load_message
    call f_print
    mov bx,KERNEL_OFFSET
    mov dh,54 ;Select 54 sectors
    mov dl, 1 ;Select Disk 1
    call f_disk_load ;Load the kernel to the space between 0x1000 and 0x7c00
    ret

[bits 16]
;Switch to protected mode
switch_to_protected_mode:
    cli ;Neccessary disabling of interuppts
    lgdt [gdt_descriptor] ;Load GDT

    mov eax, cr0 ;set the first bit of cr0 to make the switch
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_protected_mode ;make the far jump in order to flush cache

;protected mode 32bit segment
[bits 32]
init_protected_mode:
    mov ax,DATA_SEG ;move segment pointers to new locations
    mov ds,ax
    mov ss,ax
    mov es,ax
    mov fs,ax
    mov gs,ax

    mov ebp, 0x90000 ;Move the stack to free space
    mov esp,ebp

    mov ebx, greeting_pm
    call f_print_pm
    call KERNEL_OFFSET
    jmp $
[bits 16]
;String constants
greeting:
    db "Greetings from 16bit real mode!" ,0xa,0xd,0
greeting_pm:
    db "Greetings from 32bit protected mode!",0
kernel_load_message:
    db "Loading Kernel", 0xA, 0xD,0

%include "boot/f_print.asm"
%include "boot/f_print_pm.asm"
%include "boot/load_disk.asm"
%include "boot/gdt.asm"

times 510 -( $ - $$ ) db 0 ; Pad the program for the magic number to be at the right space.
dw 0xaa55 ; Bootsector magic number.
times 512 db 0
