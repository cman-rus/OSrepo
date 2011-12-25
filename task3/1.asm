	org	0x7C00

	jmp     0x0:start
start:
        push    cs
        pop     es
        push    cs
        pop     ds
	push	cs
	pop	ss

	mov	sp, 0xffff
	sti

	mov	ah, 2
;загружать будем только стоко, скоко надо(заплатка в перле)
        mov     al, 0x13
	mov	cx, 4
	mov	bx, buf
	int	0x13

	jc	@err


	mov	cx, sp
	sub	cx, 4
	pushfd
	cmp	cx,sp
	je	ok32
	popfd
	mov	bp,not32str
	mov	bx,4
	mov	ah,3
	int	0x10
	mov	cx,18
	mov	ax,0x1301
	int	0x10
	jmp	@a
	ok32:
	popfd
	mov	ecx, 0
	xor	di, di
_tab:
        mov	eax, ecx
        push	cx
        mov	cx, 8
_mktab:
	shr	eax, 1
	jnc	mktabend
	xor	eax, 0xEDB88320
mktabend:
        loop	_mktab
        mov	[crctab+di], eax
        add	di, 4
        pop	cx

	inc	cx
	cmp	cx,0xff
	jbe	_tab

	mov	eax, 0xFFFFFFFF
	mov	ecx, [len]
	xor	esi, esi
calc:
	mov	edx, eax
	shr	edx, 8
	mov	ebx, eax
	xor	bl, [buf+esi]
	inc	esi
	and	ebx, 0xff
	shl	ebx, 2
	mov	ebx, [ebx+crctab]
	xor	ebx, edx
	mov	eax, ebx
	loop	calc
	xor	eax, 0xFFFFFFFF


	cmp	eax, [crc]
	je	crcok
	mov	bp, failstr
	mov	bx, 4
	mov	ah, 3
	int	0x10
	mov	cx, 15
	mov	ax, 0x1301
	int	0x10
@err:
	mov	bp, errstr
	mov	bx, 4
	mov	ah, 3
	int	0x10
	mov	cx,24
	mov	ax,0x1301

@a:
	cli
	hlt
	jmp	@a
crcok:
	mov	si,buf
	mov	ecx,[len]
fileout:
	mov	ah,0xe
	lodsb
	int	0x10
	dec	ecx
	test	ecx,ecx
	jnz	fileout
	jmp	@a

failstr:	db	'CRC not equal! '
errstr:	db	'Error. Execution stopped.'
not32str:	db	'Error. Not 32-bit.'
; длина перловой заплаткой
len:	dd	0x89abcdef
;crc перловой заплаткой
crc:	dd	0x89abcdef
	times	510-($-$$) db 0
	db	0x55
	db	0xaa
crctab:	times	256 dd 0
buf:	db	0
