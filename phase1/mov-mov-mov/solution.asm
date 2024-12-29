section .rodata
sfmt:	db "%ld%ld", 0
pfmt:	db "%ld", 10, 0

section .bss
zero:	resb 8
X:	resb 8
Y:	resb 8
ans:	resb 8

section	.data

sub0:
%assign i 0
%rep 65536
	dw ((i & 255) - (i >> 8) - 0) & 511
%assign i i+1
%endrep

sub1:
%assign i 0
%rep 65536
	dw ((i & 255) - (i >> 8) - 1) & 511
%assign i i+1
%endrep

subc:
	dq	sub0
	dq	sub1

section .text

extern printf
extern scanf

foo:
	mov	[X], rdi
	mov	[Y], rsi
	mov	rax, [zero]
	mov	rcx, [zero]
%assign i 0
%rep 8
	mov	al, [X + i]
	mov	ah, [Y + i]
	mov	rdx, [subc + 8*rcx]
	mov	ax, [rdx + 2*rax]
	mov	cl, ah
	mov	[ans + i], al
%assign i i+1
%endrep
	mov	rax, [ans]
	ret

global main
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 16

	lea	rdi, [sfmt]
	lea	rsi, [rsp]
	lea	rdx, [rsp+8]
	call	scanf

	mov	rdi, [rsp]
	mov	rsi, [rsp+8]
	call	foo

	lea	rdi, [pfmt]
	mov	rsi, rax
	call	printf

	add	rsp, 16
	pop	rbp
	xor	eax, eax
	ret

section .note.GNU-stack
