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

.macro print_long
        enter   0
        larl    %r2, pif
        call    printf
        leave   0
.endm

.macro  read_char       # Input is in r2
        enter   8
        larl    %r2, rcf
        lay     %r3, 167(%r15)
        call    scanf
        lb      %r2, 167(%r15)
        leave   8
.endm

.data
.align 8
pif:    .asciz  "%lu\n"
.align 8
rcf:    .asciz  "%c"
.align 8
in:     .zero   100000

.text
.global main

main:
        enter   8
        larl    %r6, in
        xgr     %r7, %r7
get_input:
        read_char
        cgfi    %r2, '\n'
        je      begin
        stc     %r2, 0(%r6, %r7)
        agfi    %r7, 1
        j       get_input
begin:
        agfi    %r7, -1
done_input:
        lb      %r2, 0(%r6, %r7)
        agfi    %r7, -1
        cgfi    %r7, -1
        jl      done
        cfi     %r2, '+'
        je      add
        cfi     %r2, '-'
        je      minuse
        cfi     %r2, '*'
        je      mul
        lgfi    %r3, '0'
        sgr     %r2, %r3
        stg     %r2, 0(%r15)
        lay     %r15, -8(%r15)
        j       done_input
add:
        lay     %r15, 8(%r15)
        lg      %r8, 0(%r15)
        ag      %r8, 8(%r15)
        stg     %r8, 8(%r15)
        j       done_input
minuse:
        lay     %r15, 8(%r15)
        lg      %r8, 0(%r15)
        sg      %r8, 8(%r15)
        stg     %r8, 8(%r15)
        j       done_input
mul:
        lay     %r15, 8(%r15)
        lg      %r8, 0(%r15)
        msg     %r8, 8(%r15)
        stg     %r8, 8(%r15)
        j       done_input

done:
        lay     %r15, 8(%r15)
        lg      %r3, 0(%r15)
        print_long
de:
        leave   8
        xgr     %r2, %r2
        ret