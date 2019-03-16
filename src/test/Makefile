passes := BranchCoverage
#BlockCoverage

tests := branch switch optimizedSwitch loop virtualCall

srcDir := .
projectDir := ../..
buildDir := $(projectDir)/build
binDir := $(buildDir)/test

passLibraries := $(passes:%=$(buildDir)/lib%Pass.so)
passRuntimes := $(passes:%=$(buildDir)/lib%Runtime.a)

passLibraryArgs := $(passLibraries:%=-load=%)
passArgs := $(passes:%=-%)

flags := -S -emit-llvm -flto -fwhole-program-vtables


sourcesWithExtensions := $(shell find $(srcDir) -name "*.cpp" -or -name "*.c")
sourcesNoCppExtensions := $(sourcesWithExtensions:%.cpp=%)
sourcesNoCExtensions := $(sourcesNoCppExtensions:%.c=%)
sources := $(sourcesNoCExtensions)
LLVM_IRs := $(sources:%=$(binDir)/%.ll)
optimizedLLVM_IRs := $(sources:%=$(binDir)/%.opt.ll)
assemblies := $(sources:%=$(binDir)/%.s)
executablesOut := $(tests:%=$(binDir)/%.out)
executables :=$(tests:%=$(binDir)/%)

all: $(tests:%=%.out)
	

# compile C to LLVM IR
$(binDir)/%.ll: $(srcDir)/%.c
	mkdir -p $(dir $@)
	clang $(flags) $< -o $@
.PRECIOUS: $(binDir)/%.ll

# compile C++ to LLVM IR
$(binDir)/%.ll: $(srcDir)/%.cpp
	mkdir -p $(dir $@)
	clang++ $(flags) $< -o $@
.PRECIOUS: $(binDir)/%.ll

# optimizize LLVM IR
$(binDir)/%.opt.ll: $(binDir)/%.ll
	opt $(passLibraryArgs) $(passArgs) -S < $< > $@
.PRECIOUS: $(binDir)/%.opt.ll

# compile optimized LLVM IR to assembly
$(binDir)/%.s: $(binDir)/%.opt.ll
	clang++ -S $< $(passRuntimes) -o $@
.PRECIOUS: $(binDir)/%.s

# compile to optimized LLVM IR to executable
$(binDir)/%.out: $(binDir)/%.opt.ll
	clang++ $< $(passRuntimes) -o $@
.PRECIOUS: $(binDir)/%.out

$(binDir)/%: $(binDir)/%.out
	cp $< $@
.PRECIOUS: $(binDir)/%

%.out: $(binDir)/%
	@echo $@
.PHONY: %.out

%.run: $(binDir)/%
	./$<
.PHONY: %.run

clean:
	rm -f $(LLVM_IRs) $(optimizedLLVM_IRs) $(assemblies) $(executablesOut) $(executables)
.PHONY: clean

misc:
	@echo $(sources)
