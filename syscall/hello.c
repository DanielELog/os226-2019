
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	const char *msg = "Hello, World!\n";
	const int len = strlen(msg);
	write(1, msg, len);
	exit(0);
	return 0;
}
