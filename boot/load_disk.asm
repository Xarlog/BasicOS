; load DH sectors to ES : BX from drive DL
[bits 16]
f_disk_load:
    push dx ; Remember the number of sectors to be read on the stack
    mov ah , 0x02 ; BIOS read sector function
    mov al , dh   ; Read DH sectors
    mov ch , 0x00 ; Select cylinder 0
    mov dh , 0x00 ; Select head 0
    mov cl , 0x01 ; Start reading from *first second sector ( i.e.
    ; after the boot sector )
    int 0x13 ; BIOS interrupt
    jc disk_error ; Jump if error ( i.e. carry flag set )
    pop dx ; Restore DX from the stack
    cmp dh , al ; if AL ( sectors read ) != DH ( sectors expected )
    jne disk_error ; display error message
    ret

disk_error:
    mov bx , DISK_ERROR_MSG
    call f_print
    jmp $

DISK_ERROR_MSG:
    db " Disk read error ! " , 0