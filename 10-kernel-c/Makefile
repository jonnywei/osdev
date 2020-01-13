function.o:function.c
	gcc -ffreestanding -c function.c -o function.o
	objdump -d function.o

function.bin : function.o
	ld -o function.bin -Ttext 0x0 --oformat binary function.o