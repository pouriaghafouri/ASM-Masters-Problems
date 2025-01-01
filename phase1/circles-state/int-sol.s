global main
extern printf
extern scanf
section .text
main: 
    sub rsp, 8

    lea rdi, [sfm]
    lea rsi, [x1]
    lea rdx, [y1]
    lea rcx, [r1]
    call scanf

    lea rdi, [sfm]
    lea rsi, [x2]
    lea rdx, [y2]
    lea rcx, [r2]
    call scanf


    mov rax, [x1]
    sub rax, [x2]
    imul rax, rax

    mov rcx, [y1]
    sub rcx, [y2]
    imul rcx, rcx

    add rax, rcx ; rax = x2 + y2 = d2

    mov rcx, [r1]
    sub rcx, [r2]
    imul rcx, rcx ; rcx = (r1 - r2)2

    mov rdx, [r1]
    add rdx, [r2]
    imul rdx, rdx ; rdx = (r1 + r2)2

    
    cmp rax, rcx
    jl prin
    cmp rax, rdx
    jg prout

prtouch:
    lea rdi, [touch]
    call printf
    
    jmp done_main

prin:
    lea rdi, [in]
    call printf

    jmp done_main

prout:
    lea rdi, [out]
    call printf
    
    jmp done_main

done_main:
    add rsp, 8
    ret


section .data
sfm: db "%lld%lld%lld", 0
x1: dq 0
y1: dq 0
r1: dq 0
    
x2: dq 0
y2: dq 0
r2: dq 0

in: db "inside", 10,  0
out: db "outside", 10,  0
touch: db "touch", 10,  0
