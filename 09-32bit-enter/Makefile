run:boot_sect_loop.bin
	qemu-system-i386 boot_sect_loop.bin
boot_sect_loop.bin: 32bit-main.asm
	nasm -f bin 32bit-main.asm -o boot_sect_loop.bin
clean:
	rm boot_sect_loop.bin
