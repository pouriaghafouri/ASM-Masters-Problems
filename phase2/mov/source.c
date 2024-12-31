#include <stdio.h>

int f(unsigned int a, unsigned int b) {
	return a * b == 2308508647;
}

int main() {
	unsigned int a, b;
	scanf("%u %u", &a, &b);
	puts(f(a, b) ? "YEP" : "NOPE");
	return 0;
}
