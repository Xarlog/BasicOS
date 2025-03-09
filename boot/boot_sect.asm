[org 0x7c00] ;set program origin

mov bp, 0x8000 ;set up stack
mov sp,bp

mov ah, 0x0e ;set up rolling typing


mov bx, greeting
call f_print
call f_load_kernel
call switch_to_protected_mode
jmp $;end loop

%include "boot/f_print.asm"

greeting:
    db "Greetings from 16bit real mode! This is an absurdly simplistic and useless operating system." ,0xa,0xd,0
greeting_pm:
    db "Greetings from 32bit protected mode!",0
;GDT
gdt_start:
gdt_null:
    dd 0x0  ;mandatory null descriptor
    dd 0x0
gdt_code:
    ; base =0 x0 , limit =0 xfffff ,
    ; 1 st flags : ( present )1 ( privilege )00 ( descriptor type )1 -> 1001 b
    ; type flags : ( code )1 ( conforming )0 ( readable )1 ( accessed )0 -> 1010 b
    ; 2 nd flags : ( granularity )1 (32 - bit default )1 (64 - bit seg )0 ( AVL )0 -> 1100 b
    dw 0xffff   ; limit 0-15
    dw 0x0      ; Base 0-15
    db 0x0      ; Base 16-23
    db 10011010b;flags 1st type
    db 11001111b;flags 2nd , Limit 16-23
    db 0x0      ;Base 24-31
;data segment descriptor
gdt_data:
    ; Same as code segment except for the type flags :
    ; type flags : ( code )0 ( expand down )0 ( writable )1 ( accessed )0 -> 0010 b
    dw 0xffff   ; limit 0-15
    dw 0x0      ; Base 0-15
    db 0x0      ; Base 16-23

    db 10010010b;flags 1st type
    db 11001111b;flags 2nd , Limit 16-23
    db 0x0      ;Base 24-31
;for size calculation
gdt_end:

;GDT descriptor
gdt_descriptor:
    dw gdt_end-gdt_start-1;size
    dd gdt_start ;gdt start

; Define some handy constants for the GDT segment descriptor offsets , which
; are what segment registers must contain when in protected mode. For example ,
; when we set DS = 0 x10 in PM , the CPU knows that we mean it to use the
; segment described at offset 0 x10 ( i.e. 16 bytes ) in our GDT , which in our
; case is the DATA segment (0 x0 -> NULL ; 0 x08 -> CODE ; 0 x10 -> DATA )
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

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
KERNEL_OFFSET equ 0x1000
f_load_kernel:
    mov bx, kernel_load_message
    call f_print
    mov bx,KERNEL_OFFSET
    mov dh,54 ;initially 15 now the entire space between 0x1000 and 0x7c00
    mov dl, 1
    call f_disk_load
    ret
kernel_load_message:
    db "Loading Kernel", 0xA, 0xD,0
%include "boot/f_print_pm.asm"
%include "boot/load_disk.asm"
times 510 -( $ - $$ ) db 0 ; When compiled , our program must fit into 512 bytes ,
dw 0xaa55 ; Last two bytes ( one word ) form the magic number ,
; so BIOS knows we are a boot sector.
times 512 db 0
