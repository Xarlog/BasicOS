[bits 32]
;Useful constanst
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f
;print a null terminated string from ebx
f_print_pm:
    pusha
    mov edx, VIDEO_MEMORY

l_print_pm_loop:
    mov al,[ebx]
    mov ah,WHITE_ON_BLACK

    cmp al,0    ;check for null
    je l_print_pm_done

    mov [edx],ax    ;store char in character cell

    add ebx,1 ;next char
    add edx,2 ;next cell

    jmp l_print_pm_loop
l_print_pm_done:
    popa
    ret
;debug signal
f_ping_pm:
    pusha
    mov al, 'P'
    mov ah, WHITE_ON_BLACK
    mov [VIDEO_MEMORY],ax
    popa
    ret