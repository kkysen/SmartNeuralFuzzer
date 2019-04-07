#include <cstdio>

extern "C"
void loopTest(int n) {
	for (int i = 0; i < n; i++) {
		printf("%d\n", i);
	}
}

int main([[maybe_unused]] int argc, char** argv) {
    int n = 0;
    sscanf(argv[1], "%d", &n);
	loopTest(n);
	return 0;
}
