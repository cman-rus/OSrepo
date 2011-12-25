SOURCES=t.o

CFLAGS=-std=c99
LDFLAGS=-Ttmp

all: $(SOURCES) link

clean:
	-rm t.o a.out b.out first

link:
	ld $(LDFLAGS) $(SOURCES)
	objcopy -O binary a.out b.out
	nasm first.asm 
	cat first b.out  > load
