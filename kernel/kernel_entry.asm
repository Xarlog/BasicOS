[bits 32]
[extern ___main] ;Finds the _main function in the kernel to make sure that it is the entrypoint.
call ___main ; invoke kernel
jmp $