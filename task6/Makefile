all:
	gcc -c -std=c99 t.c 
	ld -T  tmp t.o 
	objcopy -O binary a.out b.out
	nasm first.asm 
	cat first b.out  > load
	rm t.o
	rm a.out
	rm b.out
	rm first
