#include <iostream>
#include <random>
#include <string>
#include <cstdio>
#include <cmath>
using namespace std;

#define errif0(val, str) do { if (!(val)) { perror(str); exit(1); } } while (0)

FILE *input_file = stdout, *output_file = stdout;

void gen_values(int cnt, double *vals)
{
	fprintf(input_file, "%d\n", cnt);
	for (int i = 0; i < cnt; i++) {
		double x = vals[i];
		double y = erf(x);
		long a = *(long *)&x;
		long b = *(long *)&y;
		fprintf(input_file, "%016lx\n", a);
		fprintf(output_file, "%016lx\n", b);
	}
}

void gen_longs(int cnt, long *vals)
{
	fprintf(input_file, "%d\n", cnt);
	for (int i = 0; i < cnt; i++) {
		double x = *(double *)&vals[i];
		double y = erf(x);
		long a = *(long *)&x;
		long b = *(long *)&y;
		fprintf(input_file, "%016lx\n", a);
		fprintf(output_file, "%016lx\n", b);
	}
}

void gen_range(int cnt, double mn, double mx, long seed)
{
	fprintf(input_file, "%d\n", cnt);
	mt19937_64 rd(seed);
	uniform_real_distribution<> dis(mn, mx);
	while (cnt--) {
		double x = dis(rd);
		double y = erf(x);
		long a = *(long *)&x;
		long b = *(long *)&y;
		fprintf(input_file, "%016lx\n", a);
		fprintf(output_file, "%016lx\n", b);
	}
}

void gen_longrands(int cnt, long seed)
{
	fprintf(input_file, "%d\n", cnt);
	mt19937_64 rd(seed);
	while (cnt--) {
		long foo = rd();
		double x = *(double *)&foo;
		double y = erf(x);
		long a = *(long *)&x;
		long b = *(long *)&y;
		fprintf(input_file, "%016lx\n", a);
		fprintf(output_file, "%016lx\n", b);
	}
}

void usage(const char *name)
{
	cerr << "usage:\n";
	cerr << name << " <input file> <output file> range <cnt> <min value> <max value> <seed>\n";
	cerr << name << " <input file> <output file> fixed <values...>\n";
	cerr << name << " <input file> <output file> longs <values...>\n";
	cerr << name << " <input file> <output file> longrand <cnt> <seed>\n";
}

int main(int argc, char **argv)
{
	if (argc < 5) {
		usage(argv[0]);
		return 2;
	}

	if ("-"s != argv[1])
		errif0(input_file = fopen(argv[1], "wb"), "fopen input_file");
	if ("-"s != argv[2])
		errif0(output_file = fopen(argv[2], "wb"), "fopen output_file");

	string test = argv[3];

	if (test == "fixed") {
		double *vals = new double[argc - 4];
		for (int i = 4; i < argc; i++) {
			string s = argv[i];
			vals[i - 4] = stod(s);
		}
		gen_values(argc - 4, vals);
		delete[] vals;
	}

	if (test == "longs") {
		long *vals = new long[argc - 4];
		for (int i = 4; i < argc; i++) {
			string s = argv[i];
			vals[i - 4] = stol(s);
		}
		gen_longs(argc - 4, vals);
		delete[] vals;
	}

	if (test == "range") {
		gen_range(stoi(argv[4]), stod(argv[5]), stod(argv[6]), stol(argv[7]));
	}

	if (test == "longrands") {
		gen_longrands(stoi(argv[4]), stol(argv[5]));
	}
}
