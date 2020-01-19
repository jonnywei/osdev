C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c mm/*.c fs/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h  libc/*.h mm/*.h fs/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o} 

# Change this if your cross-compiler is somewhere else
CC = gcc
GDB = gdb
# -g: Use debugging symbols in gcc
CFLAGS = -g -m32
LD = ld -m elf_i386

# First rule is run by default
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ 

run: os-image.bin initrd.img
	qemu-system-i386 -fda os-image.bin -fdb initrd.img

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf initrd.img
	qemu-system-i386 -s -fda os-image.bin  -fdb initrd.img -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o mm/*.o fs/*.o

make_initrd: make_initrd.c
	${CC}   make_initrd.c -o make_initrd

initrd.img: make_initrd
	 ./make_initrd test.txt test.txt test2.txt test2.txt


