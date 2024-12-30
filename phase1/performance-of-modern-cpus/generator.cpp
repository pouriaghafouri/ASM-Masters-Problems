#include <iostream>
#include <random>
#include <string>
#include <cstdio>
#include <cassert>
using namespace std;

#define errif0(val, str) do { if (!(val)) { perror(str); exit(1); } } while (0)
#define errif(val, str) do { if (val) { perror(str); exit(1); } } while (0)

#define MINN 16
#define MAXN 100000
#define MINQ 1
#define MAXQ 300000

FILE *input_file = stdout;
mt19937_64 rd;
int global_n;

void gen_init(int n, int q)
{
	assert(MINN <= n && n <= MAXN);
	assert(MINQ <= q && q <= MAXQ);
	global_n = n;
	fprintf(input_file, "%d\n", n);
	for (int i = 0; i < n-1; i++)
		fprintf(input_file, "%hu ", (unsigned short)rd());
	fprintf(input_file, "%hu\n%d\n", (unsigned short)rd(), q);
}

void gen_query(int q, int l, int r, unsigned short x)
{
	assert(1 <= q && q <= 3);
	assert(1 <= l && l <= r && r <= global_n);
	assert((r-l+1)%16 == 0);
	if (q == 3)
		fprintf(input_file, "%d %d %d\n", q, l, r);
	else
		fprintf(input_file, "%d %d %d %hu\n", q, l, r, x);
}
void gen_query(int q, int l, int r)
{
	gen_query(q, l, r, (unsigned short)rd());
}

unsigned long rd_range(unsigned long mn, unsigned long mx)
{
	assert(mn <= mx);
	return rd()%(mx-mn+1)+mn;
}

void gen_q_len(int q, int n, size_t len)
{
	int l = rd_range(1, n - len + 1);
	int r = l + len - 1;
	gen_query(q, l, r);
}

void gen_q_all(int q, int n)
{
	int l = 2;
	int r = n;
	while ((r-l+1)%16)
		r--;
	gen_query(q, l, r);
}

void gen_q_rand(int q, int n)
{
begin:
	int l = rd_range(1, n);
	int r = rd_range(1, n);
	if (l > r)
		swap(l, r);
	int len = r-l+1;
	if (len%16)
		goto begin;
	gen_query(q, l, r);
}

void gen_small()
{
	int n = rd_range(MINN, 100);
	int q = rd_range(MINQ, 100);
	gen_init(n, q);
	while (q--)
		gen_q_rand(rd_range(1, 3), n);
}

void gen_allx(int x)
{
	int n = MAXN;
	int q = MAXQ;
	gen_init(n, q);
	for (int i = 0; i < q-1; i++)
		gen_q_all(x, n);
	gen_q_all(3, n);
}

void gen_cycle()
{
	int n = MAXN;
	int q = MAXQ;
	gen_init(n, q);
	for (int i = 0; i < q; i++)
		gen_q_all(i%3+1, n);
}

void gen_all1() { gen_allx(1); }
void gen_all2() { gen_allx(2); }
void gen_all3() { gen_allx(3); }

void gen_random()
{
	int n = rd_range(MINN, MAXN);
	int q = rd_range(MINQ, MAXQ);
	gen_init(n, q);
	while (q--)
		gen_q_rand(rd_range(1, 3), n);
}

void gen_randombig()
{
	int n = rd_range(MAXN-16, MAXN-1);
	int q = rd_range(MAXQ-16, MAXQ-1);
	gen_init(n, q);
	while (q--) {
		int t = rd_range(1, 3);
		int len = n - n%16;
		gen_q_len(t, n, len);
	}
}

void gen_random_small3()
{
	int n = rd_range(MAXN-16, MAXN-1);
	int q = rd_range(MAXQ-16, MAXQ-1);
	gen_init(n, q);
	while (q--) {
		int t = rd_range(1, 3);
		if (t != 3)
			gen_q_rand(t, n);
		else
			gen_q_len(t, n, 16);
	}
}

void gen_random_chunk16()
{
	int n = MAXN;
	int q = MAXQ;
	gen_init(n, q);
	while (q--) {
	begin:
		int l = rd_range(0, n-1);
		int r = rd_range(0, n-1);
		l -= l%16;
		r -= r%16;
		r += 16;
		if (l == r)
			goto begin;
		if (l > r)
			swap(l, r);
		gen_query(rd_range(1, 3), l+1, r);
	}
}

void gen_random_small3_chunk16()
{
	int n = MAXN;
	int q = MAXQ;
	gen_init(n, q);
	while (q--) {
	begin:
		int l = rd_range(0, n-1);
		int r = rd_range(0, n-1);
		l -= l%16;
		r -= r%16;
		r += 16;
		if (l == r)
			goto begin;
		if (l > r)
			swap(l, r);
		int t = rd_range(1, 3);
		if (t == 3)
			r = l + 16;
		gen_query(rd_range(1, 3), l+1, r);
	}
}

void usage(const char *name)
{
	cerr << "Usage: " << name << " <input file> <test set> <seed>\n";
}

int main(int argc, char **argv)
{
	if (argc != 4) {
		usage(argv[0]);
		return 2;
	}

	if ("-"s != argv[1])
		errif0(input_file = fopen(argv[1], "wb"), "fopen input_file");

	rd.seed(stoul(argv[3], NULL, 0));

	string test_set = argv[2];

	if (test_set == "small") gen_small();
	if (test_set == "all1") gen_all1();
	if (test_set == "all2") gen_all2();
	if (test_set == "all3") gen_all3();
	if (test_set == "cycle") gen_cycle();
	if (test_set == "random") gen_random();
	if (test_set == "randombig") gen_randombig();
	if (test_set == "random_small3") gen_random_small3();
	if (test_set == "random_chunk16") gen_random_chunk16();
	if (test_set == "random_small3_chunk16") gen_random_small3_chunk16();
}
