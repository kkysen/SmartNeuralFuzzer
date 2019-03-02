all: BranchCoveragePass.so

HEADERS := alignment.h AllocaArgs.h BranchCoveragePass.h Constants.h debug.h IRBuilderExt.h LLVMArray.h LoadStore.h numbers.h Types.h

BranchCoveragePass.so: BranchCoveragePass.cpp $(HEADERS)
	clang++ -shared -fpic --std=c++17 -fno-exceptions -fno-rtti -g -I $(WORKSPACE)/C++/llvm-project/llvm/include -I $(WORKSPACE)/C++/llvm-project/build/clang/fewTargets/Release/include BranchCoveragePass.cpp -o $@ -Wall -Werror

MAIN := opt -load ./BranchCoveragePass.so -branch-coverage -S < $(WORKSPACE)/misc/main.ll > transformed.ll

run: all
	$(MAIN)

valgrind: all
	valgrind $(MAIN)
