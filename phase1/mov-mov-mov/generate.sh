#!/bin/sh
set -e
g++ generator.cpp -o gen
mkdir -p tests

./gen tests/0.in tests/0.out 7 3
./gen tests/1.in tests/1.out 7 -3
./gen tests/2.in tests/2.out 0 -1
./gen tests/3.in tests/3.out 4294967296 1
./gen tests/4.in tests/4.out 4294967295 -1
./gen tests/5.in tests/5.out -9223372036854775808 1
./gen tests/6.in tests/6.out 9223372036854775807 -1
./gen tests/7.in tests/7.out 9223372036854775807 9223372036854775807
./gen tests/8.in tests/8.out -9223372036854775808 -9223372036854775808
./gen tests/9.in tests/9.out -9223372036854775808 9223372036854775807
./gen tests/10.in tests/10.out 9223372036854775807 -9223372036854775808

for i in `seq 11 19`; do
	./gen tests/$i.in tests/$i.out $i
done
