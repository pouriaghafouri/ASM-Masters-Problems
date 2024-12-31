default rel

%macro myenter 1 ; %1 must be a multiple of 16
	push	rbp
	mov	rbp, rsp
	push	rbx
	push	r12
	push	r13
	push	r14
	push	r15
	sub	rsp, %1 + 8 ; rsp must be a multiple of 16
%endmacro

%macro myleave 1
	add	rsp, %1 + 8
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	rbx
	pop	rbp
%endmacro

%macro mycall 1
	push	rcx
	push	rdx
	push	rsi
	push	rdi
	push	r8
	push	r9
	push	r10
	push	r11
	call	%1
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	rdi
	pop	rsi
	pop	rdx
	pop	rcx
%endmacro

section .rodata
sd:	db "%u", 0
sw:	db "%hu", 0
squery:	db "%d %d %d", 0
pw:	db "%hu", 10, 0

section	.data
alignb	8
perform: dq perform_1, perform_2, perform_3


section .bss
alignb	32
A:	resw	100032
n:	resd	1
query:	resd	4

section .text

extern scanf
extern printf

read_A:
	myenter	0
	lea	rdi, [sd]
	lea	rsi, [n]
	mycall	scanf wrt ..plt
	mov	edx, [n]
	xor	ecx, ecx
	lea	r8, [A]
.loop:
	lea	rdi, [sw]
	lea	rsi, [r8 + 2*rcx]
	mycall	scanf wrt ..plt
	inc	ecx
	cmp	ecx, edx
	jne	.loop
	myleave	0
	ret

read_query:
	myenter 0
	lea	rdi, [squery]
	lea	rsi, [query]
	lea	rdx, [query + 4]
	lea	rcx, [query + 8]
	mycall	scanf wrt ..plt
	cmp	DWORD [query], 3
	je	.skip
	lea	rdi, [sd]
	lea	rsi, [query + 12]
	mycall	scanf wrt ..plt
.skip:
	myleave	0
	ret

perform_1:
	myenter 0
	lea	r8, [A]
	lea	rcx, [r8 + 2*rdi]
	lea	rsi, [r8 + 2*rsi]
.loop:
	movzx	eax, WORD [rcx]
	add	eax, edx
	mov	WORD [rcx], ax

	movzx	eax, WORD [rcx+2]
	add	eax, edx
	mov	WORD [rcx+2], ax

	movzx	eax, WORD [rcx+4]
	add	eax, edx
	mov	WORD [rcx+4], ax

	movzx	eax, WORD [rcx+6]
	add	eax, edx
	mov	WORD [rcx+6], ax

	add	rcx, 8
	cmp	rcx, rsi
	jne	.loop
	myleave	0
	ret

perform_2:
	myenter 0
	vmovd	xmm0, edx
	vpbroadcastw	ymm0, xmm0
	lea	r8, [A]
	lea	rcx, [r8 + 2*rdi]
	lea	rdx, [r8 + 2*rsi]
.loop:
	vmovdqu	ymm1, [rcx]
	vpxor	ymm1, ymm1, ymm0
	vmovdqu	[rcx], ymm1
	add	rcx, 32
	cmp	rcx, rdx
	jne	.loop
	myleave	0
	ret

perform_3:
	myenter 32
	lea	r8, [A]
	lea	rcx, [r8 + 2*rdi]
	lea	rdx, [r8 + 2*rsi]
	vpcmpeqw	ymm0, ymm0, ymm0
.loop:
	vpminuw	ymm0, [rcx]
	add	rcx, 32
	cmp	rcx, rdx
	jne	.loop

	vmovdqu	[rsp], ymm0
	xor	ecx, ecx
	mov	eax, 65535
.loop2:
	movzx	ebx, WORD [rsp + rcx]
	cmp	eax, ebx
	cmova	eax, ebx
	add	ecx, 2
	cmp	ecx, 32
	jne	.loop2

	lea	rdi, [pw]
	mov	esi, eax
	mycall	printf wrt ..plt

	myleave	32
	ret

global main
main:
	myenter	16
	mycall	read_A
	lea	rdi, [sd]
	lea	rsi, [rsp]
	mycall	scanf wrt ..plt
	mov	r8d, [rsp]
	lea	r9, [perform]
.loop:
	mycall	read_query
	mov	eax, [query]
	mov	edi, [query + 4]
	mov	esi, [query + 8]
	mov	edx, [query + 12]
	dec	edi
	mov	rax, [r9 + 8*(rax - 1)]
	mycall	rax
	dec	r8
	jnz	.loop

	myleave 16
	xor	eax, eax
	ret

section .note.GNU-stack
