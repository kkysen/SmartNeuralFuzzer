MAIN := BranchCoveragePass

all: $(MAIN).so
.PHONY: all

HEADERS := alignment.h AllocaArgs.h $(MAIN).h Constants.h debug.h IRBuilderExt.h LLVMArray.h LoadStore.h numbers.h Types.h

LLVM_VERSION := $(shell llvm-config --version)
IS_NEW_LLVM_VERSION := $(findstring 9.,$(LLVM_VERSION))

HOST_FLAGS := -I $(WORKSPACE)/C++/llvm-project/llvm/include \
-I $(WORKSPACE)/C++/llvm-project/build/clang/fewTargets/Release/include \
--std=c++11 -fno-exceptions -fno-rtti

REMOTE_FLAGS := $(shell llvm-config --cxxflags)


ifeq ($(IS_NEW_LLVM_VERSION),9.)
FLAGS := $(REMOTE_FLAGS)
else
FLAGS := $(HOST_FLAGS)
endif

$(MAIN).so: $(MAIN).cpp $(HEADERS)
	clang++ -shared -fpic $(FLAGS) --std=c++17  -g  $(MAIN).cpp -o $@ -Wall -Werror

CMD := opt -load ./$(MAIN).so -branch-coverage -S < test/main.ll > test/transformed.ll

run: all
	$(CMD)
.PHONY: run

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=definite $(CMD)
.PHONY: valgrind

input:
	clang++ -S -emit-llvm test/main.cpp -o test/main.ll
.PHONY: input

output:
	clang++ test/transformed.ll -o test/main
.PHONY: output

runOutput:
	./test/main
.PHONY: runOutput

clean:
	rm -f $(MAIN).so
.PHONY: clean

misc:
	echo $(FLAGS)
.PHONY: misc
