#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "init.h"

int main(int argc, char *argv[]) {
	void *base = sbrk(0);

	init(base);

	volatile int *b0 = (volatile int *)base;

	volatile int *b4 /* = b0 + 4 */;
	// compiler is too smart and optimizes all accesses
	// to b4 as b0 with extra offset. Use inline asm to
	// prevent optimization and compile b4 as another
	// base pointer
	__asm__ __volatile__(
		"nop"
		: "=a"(b4)
		: "a"(b0 + 4)
	);

	printf("%d\n", b0[0]);
	printf("%d\n", b0[0]);
	printf("%d\n", b0[0]);
	printf("%d\n", b0[0]);
	printf("\n");
	printf("%d\n", b0[1]);
	printf("%d\n", b0[2]);
	printf("%d\n", b0[3]);
	printf("\n");
	printf("%d\n", b4[0]);
	printf("%d\n", b4[1]);
	printf("%d\n", b4[2]);
	printf("%d\n", b4[3]);
	printf("\n");
	printf("%s %d\n", "_", b0[0]);
	printf("%s %d\n", "_", b4[4]);

	return 0;
}
