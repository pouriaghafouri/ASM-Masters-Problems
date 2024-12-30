#!/bin/sh
set -e
g++ generator.cpp -o gen
mkdir -p tests

create() {
	./gen tests/$1.in $2 $1
}

cp 0.in tests/
create 1 small
create 2 small
create 3 cycle
create 4 all1
create 5 all2
create 6 all3
create 7 randombig
create 8 randombig
create 9 randombig
create 10 randombig
create 11 random
create 12 random
create 13 random
create 14 random
create 15 random_small3
create 16 random_small3
create 17 random_chunk16
create 18 random_small3_chunk16
create 19 random_small3_chunk16
