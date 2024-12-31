.macro enter size
        stmg    %r6, %r15, 48(%r15)
        lay     %r15, -(160+\size)(%r15)
.endm

.macro leave size
        lay     %r15, (160+\size)(%r15)
        lmg     %r6, %r15, 48(%r15)
.endm

.macro ret
        br      %r14
.endm

.macro call func
        brasl   %r14, \func
.endm

.macro read_long        # Input is in r2
        enter   8
        larl    %r2, rif
        lay     %r3, 160(%r15)
        call    scanf
        lg      %r2, 160(%r15)
        leave   8
.endm

.macro read_hex label
        enter   0
        larl    %r2, rff
        larl    %r3, \label
        call    scanf
        leave   0
.endm

.macro print_hex
        enter   0
        larl    %r2, pff
        call    printf
        leave   0
.endm

.data
.align 8
rif:    .asciz  "%ld"
.align 8
rff:    .asciz  "%016lx"
.align 8
pff:    .asciz  "%016lx\n"
.align 8

in:     .space  8

.text
.global main

main:
        enter   0

        read_long
        lgr     %r7, %r2
loop:
        read_hex in
        larl    %r6, in
        ld      %f0, 0(%r6)
        call    erf
        std     %f0, 0(%r6)
        lgrl    %r3, in
        print_hex
        agfi    %r7, -1
        cgfi    %r7, 0
        jne     loop

        leave   0
        xgr %r2, %r2
        ret
