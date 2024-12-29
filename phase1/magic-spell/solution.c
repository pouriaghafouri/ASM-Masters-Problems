#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char str[1<<20];

int main()
{
	unsigned long op;
	scanf("%lu%s", &op, str);
	// we also print syscall's error code
	// this shouldn't matter since it's printed to stderr
	errno = 0;
	syscall(0xfacade, op, str, strlen(str));
	perror("magic syscall");
	printf("%s\n", str);
}
