	org	0x7C00


	cli
	jmp	0x0:start
start:
	push	cs
	pop	es
	push	cs
	pop	ds
	
	mov	ah, 2
	mov	al, 0x10
	mov	bx, 0x8000
	mov	ch, 0
	mov	cl, 2	
	sti
	int	13h

	lgdt	[limit]
	
	mov	eax, cr0
	or	eax, 1
	mov	cr0, eax
	
	
	jmp	0x08:sta2

sta2:
	BITS	32

	mov	ax, 0x10 
   	mov	ds, ax 
   	mov	es, ax
   	mov	fs, ax
   	mov	gs, ax
   	mov	ss, ax


	call	0x8000

	cli
	hlt

	sti

t1:
	dd 	0x0
	dd	0x0
	dd	0x0000ffff
	dd	0x00cf9a00

	dd	0x0000ffff
	dd	0x00cf9200
	
limit	dw	24
base	dd	t1

	times	510-($-$$) db 0
	db	0x55, 0xAA
