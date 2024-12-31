#include <stdio.h>

__attribute__((naked))
long call_mov_sub(long x, long y)
{
	__asm__(
	"push	%rbx\n\t"
	"push	%rbp\n\t"
	"push	%r12\n\t"
	"push	%r13\n\t"
	"push	%r14\n\t"
	"push	%r15\n\t"
	"sub	$8, %rsp\n\t"
	"call	mov_sub\n\t"
	"add	$8, %rsp\n\t"
	"pop	%r15\n\t"
	"pop	%r14\n\t"
	"pop	%r13\n\t"
	"pop	%r12\n\t"
	"pop	%rbp\n\t"
	"pop	%rbx\n\t"
	"mov	%rdi, %rax\n\t"
	"ret\n\t"
	);
}

int main()
{
	long x, y, ans;
	scanf("%ld%ld", &x, &y);
	ans = call_mov_sub(x, y);
	printf("%ld\n", ans);
}
