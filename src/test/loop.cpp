#include <cstdio>

extern "C"
void loopTest(int argc) {
	for (int i = 0; i < argc; i++) {
		printf("%d\n", i);
	}
}

int main(int argc, char** argv) {
	loopTest(argc);
	return 0;
}
