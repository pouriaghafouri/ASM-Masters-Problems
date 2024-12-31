#!/bin/sh
set -e
s390x-linux-gnu-g++ -static generator.cpp -o gen
mkdir -p tests

cp 0.in 0.out tests/
qemu-s390x gen tests/1.in tests/1.out fixed +0 -0 +1 -1 +INF -INF +NAN -NAN
qemu-s390x gen tests/2.in tests/2.out range 100 -1 1 2
qemu-s390x gen tests/3.in tests/3.out range 99999 -1 1 3
qemu-s390x gen tests/4.in tests/4.out range 100000 -1 1 4
qemu-s390x gen tests/5.in tests/5.out range 100000 -1e-100 1e-100 5
qemu-s390x gen tests/6.in tests/6.out range 100000 -1e100 1e100 6
qemu-s390x gen tests/7.in tests/7.out range 100000 -1e-200 1e-200 7
qemu-s390x gen tests/8.in tests/8.out longs -3 -2 -1 0 1 2 3 -30 30 -1000 1000 -10000000 10000000
qemu-s390x gen tests/9.in tests/9.out longrands 100000 9
qemu-s390x gen tests/10.in tests/10.out longrands 100000 10
