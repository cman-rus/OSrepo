# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=f.o main.o common.o monitor.o gdt.o isr.o interrupt.o descriptor_tables.o 

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -march=i386 
LDFLAGS=--oformat elf32_i386 -m elf_i386 -Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel load go32 b.out

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)
	objcopy -O binary kernel b.out
	nasm go32.asm 
	cat go32 b.out  > load

.s.o:
	nasm $(ASFLAGS) $<
