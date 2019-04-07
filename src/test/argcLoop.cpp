#include <cstdio>

extern "C"
void loopTest(int n) {
	for (int i = 0; i < n; i++) {
		printf("%d\n", i);
	}
}

int main(int argc, [[maybe_unused]] char** argv) {
	loopTest(argc);
	return 0;
}
