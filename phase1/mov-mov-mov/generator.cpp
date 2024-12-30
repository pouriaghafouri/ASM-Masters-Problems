#include <iostream>
#include <random>
#include <string>
#include <cstdio>
using namespace std;

#define errif0(val, str) do { if (!(val)) { perror(str); exit(1); } } while (0)

FILE *input_file = stdout, *output_file = stdout;

// this is needed because signed integer overflow is UB in c/c++
long overflowing_sub(long x, long y)
{
	return (long)((unsigned long)x - (unsigned long)y);
}

void gen_random(long seed)
{
	mt19937_64 rd(seed);
	long x = rd();
	long y = rd();
	fprintf(input_file, "%ld %ld\n", x, y);
	fprintf(output_file, "%ld\n", overflowing_sub(x, y));
}

void gen_fixed(long x, long y)
{
	fprintf(input_file, "%ld %ld\n", x, y);
	fprintf(output_file, "%ld\n", overflowing_sub(x, y));
}

void usage(const char *name)
{
	cerr << "usage:\n";
	cerr << name << " <input file> <output file> <first value> <second value>\n";
	cerr << name << " <input file> <output file> <seed>\n";
}

int main(int argc, char **argv)
{
	if (argc != 4 && argc != 5) {
		usage(argv[0]);
		return 2;
	}

	if ("-"s != argv[1])
		errif0(input_file = fopen(argv[1], "wb"), "fopen input_file");
	if ("-"s != argv[2])
		errif0(output_file = fopen(argv[2], "wb"), "fopen output_file");

	if (argc == 5)
		gen_fixed(stol(argv[3]), stol(argv[4]));

	if (argc == 4)
		gen_random(stol(argv[3]));
}
