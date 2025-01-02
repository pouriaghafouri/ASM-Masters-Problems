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

.macro print_long       # Output is in r3
        enter   0
        larl    %r2, pif
        call    printf
        leave   0
.endm

.macro read_long        # Input is in r2
        enter   8
        larl    %r2, rif
        lay     %r3, 160(%r15)
        call    scanf
        lg      %r2, 160(%r15)
        leave   8
.endm

.macro read_string label        # Input is stored in the label
        enter   0
        larl    %r2, rsf
        larl    %r3, \label
        call    scanf
        leave   0
.endm

.macro print_string label       # Output is in the label
        enter   0
        larl    %r3, \label
        larl    %r2, psf
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

.macro print_char       # Output is in r3
        enter   0
        larl    %r2, pcf
        call    printf
        leave   0
.endm

.data
.align 8
rif:    .asciz  "%ld"
.align 8
pif:    .asciz  "%ld\n"
.align 8
rsf:    .asciz  "%s"
.align 8
psf:    .asciz  "%s"
.align 8
rcf:    .asciz  "%c"
.align 8
pcf:    .asciz  "%c"
.align 8
one:    .quad   0xffffffffffffffff
yes:    .asciz  "YES\n"
.align 8
no:     .asciz  "NO\n"
.text
.global main

main:
        enter   0

        read_long
        lgr     %r10, %r2
        read_long
        lgr     %r6, %r2
outer_loop:
        cgfi    %r6, 0
        je      done
        agfi    %r6, -1
        read_long
        lgr     %r8, %r2
        read_long
        lgr     %r7, %r2
        cgfi    %r7, 0
        je      zero
        sll     %r7, 0(%r8)
        ogr     %r10, %r7
        j       inner_loop
zero:
        agfi    %r7, 1
        sll     %r7, 0(%r8)
        larl    %r11, one
        xg      %r7, 0(%r11)
        ngr     %r10, %r7
inner_loop:
        lgr     %r11, %r10
        xgr     %r0, %r0
inner:
        lgfi    %r1, 15
        lgr     %r2, %r11
        ngr     %r11, %r1
        cgfi    %r11, 12
        je      yes_label
        lgr     %r11, %r2
        srl     %r11, 1
        agfi    %r0, 1
        cgfi    %r0, 32
        je      no_label
        j       inner
yes_label:
        print_string yes
        j       outer_loop
no_label:
        print_string no
        j       outer_loop
done:
        leave   0
        xgr %r2, %r2
        ret