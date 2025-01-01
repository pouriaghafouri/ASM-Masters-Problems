section .data
sfmt:	db	"%d%d", 0
yes:	db	"YES", 0
no:	db	"NO", 0

section	.text

extern scanf
extern puts
global main

main:
	push	rbp
	mov	rbp, rsp
	push	r8
	push	r9
	push	r10
	push	r11
	push	r12
	push	r13
	push	r14
	push	r15
	sub	rsp, 16

	lea	rdi, [sfmt]
	lea	rsi, [rsp]
	lea	rdx, [rsp+4]
	call	scanf

	mov	r8d, [rsp]
	mov	r9d, [rsp+4]
	not	r8d
	not	r9d

	mov	r10d, r8d
	mov	r11d, r9d
	and	r10d, r11d

	mov	r11d, r8d
	mov	r12d, r9d
	shl	r12d, 1
	and	r11d, r12d

	mov	r12d, r8d
	mov	r13d, r9d
	shl	r12d, 1
	and	r12d, r13d

	mov	r13d, r10d
	or	r13d, r11d
	or	r13d, r12d

	test	r13d, r13d
	jnz	.no

.yes:
	lea	rdi, [yes]
	call	puts
	jmp	.ret

.no:
	lea	rdi, [no]
	call	puts

.ret:
	add	rsp, 16
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	rbp
	xor	eax, eax
	ret
