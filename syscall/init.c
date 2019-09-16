#define _GNU_SOURCE

#include <ucontext.h>
#include <sys/ucontext.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "init.h"

int baseOffset;
int callCounter = 100000;

void sigHandler(int sig, siginfo_t *siginfo, void *ctx) {
	callCounter++;
	ucontext_t *uc = (ucontext_t *)ctx;
	uint16_t cmd = *(uint16_t *) uc->uc_mcontext.gregs[REG_RIP];
	int index = 0;
	int regRipOffset = 2;
	
	if (cmd & 0xff != 0x8b)
		return;

	if (cmd == 0x538b) {
		index = ((*(uint32_t *) uc->uc_mcontext.gregs[REG_RIP]) & 0xff0000) >> 18;
	}
	else if (cmd == 0x4d8b || cmd == 0x558b) {
		index = ((*(uint32_t *) uc->uc_mcontext.gregs[REG_RIP]) & 0xff0000) >> 18;
		index += (((int)uc->uc_mcontext.gregs[REG_RBP]) - baseOffset) >> 2;
	}

	if (cmd == 0x4d8b || cmd == 0x538b || cmd == 0x558b) {
		regRipOffset = 3;
	}
	
	if (cmd == 0x138b || cmd == 0x538b || cmd == 0x558b) {
		uc->uc_mcontext.gregs[REG_RDX] = callCounter + 1000 * index;
	}
	else if (cmd == 0x4d8b || cmd == 0x0b8b) {
		uc->uc_mcontext.gregs[REG_RCX] = callCounter + 1000 * index;
	}
	uc->uc_mcontext.gregs[REG_RIP] += regRipOffset;
}

void init(void *base) {
	baseOffset = base;
	
	struct sigaction act;
	act.sa_sigaction = sigHandler;
	act.sa_flags = SA_RESTART;
	
	sigemptyset(&act.sa_mask);
	sigaction(SIGSEGV, &act, NULL);
}
