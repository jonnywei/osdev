
all:os-image.bin


os-image.bin: boot_sect.bin kernel.bin
	cat boot_sect.bin kernel.bin > os-image.bin



run:os-image.bin
	qemu-system-i386 -fda os-image.bin



boot_sect.bin: boot_sect.asm
	nasm boot_sect.asm -f bin -o boot_sect.bin


entry.o : entry.asm	
	nasm entry.asm -f elf -o entry.o	

kernel.o : kernel.c
	gcc -m32 -ffreestanding -c kernel.c -o kernel.o

kernel.bin : entry.o kernel.o
	ld -m elf_i386  -o kernel.bin -Ttext 0x1000 entry.o kernel.o	--oformat binary

clean:
	rm *.bin *.o