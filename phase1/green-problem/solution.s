section .data
sfmt:	db	"%d", 0

section	.text

extern	scanf
extern	putchar

%macro char 1
	mov	edi, %1
	call	putchar
%endmacro

global	main
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 16

	lea	rdi, [sfmt]
	lea	rsi, [rsp]
	call	scanf

	push	rbx
	push	rbx

	char	'a'
	mov	ebx, [rsp + 16]
.loop:
	char	's'
	dec	ebx
	jnz	.loop
	char	'm'
	char	'!'
	char	10

	pop	rbx
	pop	rbx

	add	rsp, 16
	pop	rbp
	xor	eax, eax
	ret
