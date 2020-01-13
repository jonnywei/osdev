run:boot_sect_loop.bin
	qemu-system-i386 boot_sect_loop.bin
boot_sect_loop.bin: boot_sect_loop.asm
	nasm -f bin boot_sect_loop.asm -o boot_sect_loop.bin
clean:
	rm boot_sect_loop.bin
