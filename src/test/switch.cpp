#include <cstdio>

extern "C"
int switchTest(int argc) {
	switch (argc) {
        case 0:
            printf("case 0\n");
            return 1;
        case 1:
            printf("case 1\n");
            return 2;
        case 2:
            printf("case 2\n");
            return 3;
        case 5:
            printf("case 5\n");
            return 100;
        default:
            printf("default case\n");
            return 0;
    }
}

int main(int argc, [[maybe_unused]] char** argv) {
	printf("%d\n", switchTest(argc));
	return 0;
}
