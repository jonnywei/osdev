C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

OBJS = ${C_SOURCES:.c=.o}

CFLAGS = -g

all:os-image.bin


os-image.bin: boot/boot-sect.bin kernel.bin
	cat $^ > $@



run:os-image.bin
	qemu-system-i386 -fda $<


%.bin: %.asm
	nasm $< -f bin -o $@


%.o : %.asm	
	nasm $< -f elf -o $@

%.o : %.c  ${HEADERS}
	gcc -m32  ${CFLAGS} -ffreestanding -c  $< -o $@

kernel.bin : boot/entry.o ${OBJS}
	ld -m elf_i386  -o $@ -Ttext 0x1000 $^	--oformat binary

kernel.elf : boot/entry.o ${OBJS}
	ld -m elf_i386  -o $@ -Ttext 0x1000 $^	

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

clean:
	rm -rf *.bin *.o *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o