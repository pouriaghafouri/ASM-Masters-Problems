section	.data
sfmt:	db	"%lu%s", 0

section	.bss
str:	resb	10032

section	.text

extern scanf
extern strlen
extern puts

global main
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 16

	lea	rdi, [sfmt]
	lea	rsi, [rsp]
	lea	rdx, [str]
	call	scanf

	lea	rdi, [str]
	call	strlen

	mov	rdi, [rsp]
	lea	rsi, [str]
	mov	rdx, rax
	mov	eax, 0xfacade
	syscall

	lea	rdi, [str]
	call	puts

	add	rsp, 16
	pop	rbp
	xor	eax, eax
	ret

section .note.GNU-stack
