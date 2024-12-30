#include <stdio.h>
#include <stdlib.h>

#define CNT (26 + 26 + 10 + 1)

int main(int argc, char **argv)
{
	if (argc != 4) {
		fprintf(stderr, "Usage:\n%s <magic number> <seed> <length>\n", argv[0]);
		return 2;
	}
	unsigned long magic = strtoul(argv[1], NULL, 0);
	srand(atoi(argv[2]));
	int len = atoi(argv[3]);
	char valid[CNT];
	for (int i = 0; i < 26; i++) {
		valid[i] = 'a' + i;
		valid[i + 26] = 'A' + i;
	}
	for (int i = 0; i < 10; i++)
		valid[i + 52] = '0' + i;
	valid[62] = '_';
	printf("%lu ", magic);
	for (int i = 0; i < len; i++)
		putchar(valid[rand()%CNT]);
	putchar('\n');
}
