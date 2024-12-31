#!/bin/sh
set -e
nasm -felf64 $1.s -o $1.o
gcc -no-pie -z noexecstack -static -pipe -std=c17 $1.o driver.c -o $1 -lm
./$1
