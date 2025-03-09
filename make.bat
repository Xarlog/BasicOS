if not exist "bin" mkdir bin
nasm boot/boot_sect.asm -f bin -o bin/boot_sect.bin
gcc -ffreestanding  -m32 -c kernel/kernel.c -o bin/kernel.o
nasm kernel/kernel_entry.asm -f elf -o bin/kernel_entry.o
ld -mi386pe --section-alignment 4096  --image-base 0x0 -o bin/kernel.tmp bin/kernel_entry.o bin/kernel.o 
strip -s bin/kernel.tmp
objcopy -O binary bin/kernel.tmp --set-start 0x1000 bin/kernel.bin

