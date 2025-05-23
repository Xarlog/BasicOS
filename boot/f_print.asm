f_print:
    push ax
l_print_loop:
    mov al, [bx]
    int 0x10 ;print al
    add bx, 1
    cmp byte [bx], byte 0
    jne l_print_loop
    pop ax
    ret
;f_print_hex bl=value to print
f_print_hex:
    push bx
    shr bl, 4 ;select 4 ms bits
    push ax
    mov al, hex_vals
    add bl,al
    mov al, [bx]
    int 0x10
    pop ax
    pop bx
    push bx
    and bl,00001111b
    push ax
    mov al, hex_vals
    add bl,al ;select 4 ls bits
    mov al, [bx]
    int 0x10
    pop ax
    pop bx
    ret
hex_vals:
    db "0123456789ABCDEF"