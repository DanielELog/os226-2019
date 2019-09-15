
#define _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <ucontext.h>
#include <sys/ucontext.h>

void os_sighnd(int sig, siginfo_t *info, void *ctx) {
	ucontext_t *uc = (ucontext_t *) ctx;

	if (0x81cd == *(uint16_t *) uc->uc_mcontext.gregs[REG_RIP]) {
		const char *msg = (const char *) uc->uc_mcontext.gregs[REG_RAX];
		int ret = write(STDOUT_FILENO, msg, strlen(msg));
		uc->uc_mcontext.gregs[REG_RAX] = ret;
		uc->uc_mcontext.gregs[REG_RIP] += 2;
	}
}

void os_init(void) {
	struct sigaction act = {
		.sa_sigaction = os_sighnd,
		.sa_flags = SA_RESTART,
	};
	sigemptyset(&act.sa_mask);

	if (-1 == sigaction(SIGSEGV, &act, NULL)) {
		perror("signal set failed");
		exit(1);
	}
}

int os_sys_write(const char *msg) {
	int ret;
	__asm__ __volatile__(
		"int $0x81\n"
		: "=a"(ret)
		: "a"(msg)
		:
	);
	return ret;
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
