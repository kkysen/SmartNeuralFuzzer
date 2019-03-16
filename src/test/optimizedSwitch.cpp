#include <cstdio>

extern "C"
int optimizedSwitchTest(int argc) {
	switch (argc) {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 3;
        case 5:
            return 100;
        default:
            return 0;
    }
}

int main(int argc, char** argv) {
	printf("%d\n", optimizedSwitchTest(argc));
	return 0;
}
