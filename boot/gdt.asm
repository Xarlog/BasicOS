;GDT
gdt_start:
gdt_null:
    dd 0x0  ;mandatory null descriptor
    dd 0x0
gdt_code:
    ; base =0x0 , limit =0xfffff ,
    ; 1 st flags : ( present )    1 ( privilege )       00 ( descriptor type )1               -> 1001 b
    ; type flags : ( code )       1 ( conforming )      0 ( readable )        1 ( accessed )0 -> 1010 b
    ; 2 nd flags : ( granularity )1 (32 - bit default ) 1 (64 - bit seg )     0 ( AVL )     0 -> 1100 b
    dw 0xffff   ; limit 0-15
    dw 0x0      ; Base 0-15
    db 0x0      ; Base 16-23
    db 10011010b;flags 1st type
    db 11001111b;flags 2nd , Limit 16-23
    db 0x0      ;Base 24-31
;data segment descriptor
gdt_data:
    ; 1 st flags : ( present )    1 ( privilege )       00 ( descriptor type )1               -> 1001 b
    ; type flags : ( code )       0 ( expand down )     0 ( writable )        1 ( accessed )0 -> 0010 b
    ; 2 nd flags : ( granularity )1 (32 - bit default ) 1 (64 - bit seg )     0 ( AVL )     0 -> 1100 b
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

;Segment offset constants. Used to set segment registers in protected mode.
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start