
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct rec {
	const char *id;
	int cnt;
};

int main(int argc, char *argv[]) {
	int sz = 0;
	struct rec *rs = NULL;

	char in[128];
	while (EOF != scanf("%s", in)) {
		bool found = false;
		for (int i = 0; i < sz; ++i) {
			if (!strcmp(in, rs[i].id)) {
				++rs[i].cnt;
				found = true;
				break;
			}
		}
		if (!found) {
			++sz;
			rs = realloc(rs, sizeof(struct rec) * sz);
			rs[sz - 1].id = strdup(in);
			rs[sz - 1].cnt = 1;
		}
	}

	int max_i = sz - 1;
	for (int i = 0; i < sz - 1; ++i) {
		if (rs[max_i].cnt < rs[i].cnt) {
			max_i = i;
		}
	}

	if (0 <= max_i) {
		printf("%s\n", rs[max_i].id);
	}
        return 0;
}
