
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void os_init(void) {
}

int os_sys_write(const char *msg) {
	printf("%s", msg);
	/*write(STDOUT_FILENO, msg, strlen(msg));*/
	return 0;
}

void app1(void) {
	const char *msg = "Hello, World!\n";
	os_sys_write(msg);
}

int main(int argc, char *argv[]) {
	os_init();
	app1();
	return 0;
}
