#include <cstdio>

extern "C"
int branchTest(int argc) {
	if (argc == 1) {
        return 0;
    } else if (argc == 2) {
        return 1;
    } else {
        return 2;
    }
}

int main(int argc, char** argv) {
	printf("%d\n", branchTest(argc));
	return 0;
}
