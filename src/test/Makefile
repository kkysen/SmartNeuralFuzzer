passes := branch block

tests := branch switch optimizedSwitch argcLoop nLoop virtualCall staticConstructors

srcDir := .
projectDir := ../..
buildDir := $(projectDir)/build
binDir := $(buildDir)/test

passLibraries := $(shell ./find.sh pass.so $(buildDir) $(passes))
passRuntimes := $(shell ./find.sh runtime.a $(buildDir) $(passes))

passLibraryArgs := $(passLibraries:%=-load=%)
passArgs := $(passes:%=-coverage.%)

optimization := -O3
flags := $(optimization) -S -emit-llvm -flto -fwhole-program-vtables
linkLibraries := -lstdc++fs


sourcesWithExtensions := $(shell find $(srcDir) -name "*.cpp" -or -name "*.c")
sourcesNoCppExtensions := $(sourcesWithExtensions:%.cpp=%)
sourcesNoCExtensions := $(sourcesNoCppExtensions:%.c=%)

sources := $(sourcesNoCExtensions)

LLVM_IRs := $(sources:%=$(binDir)/%.ll)
instrumentedLLVM_IRs := $(sources:%=$(binDir)/%.instr.ll)
optimizedLLVM_IRs := $(sources:%=$(binDir)/%.opt.ll)
assemblies := $(sources:%=$(binDir)/%.s)
executablesOut := $(tests:%=$(binDir)/%.out)
executables :=$(tests:%=$(binDir)/%)

outputs := $(LLVM_IRs) $(instrumentedLLVM_IRs) $(optimizedLLVM_IRs) $(assemblies) $(executablesOut) $(executables)

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

# instrument LLVM IR
$(binDir)/%.instr.ll: $(binDir)/%.ll
	opt $(passLibraryArgs) $(passArgs) -S < $< > $@
.PRECIOUS: $(binDir)/%.instr.ll

# optimizize LLVM IR
$(binDir)/%.opt.ll: $(binDir)/%.instr.ll
	opt $(optimization) -S < $< > $@
.PRECIOUS: $(binDir)/%.opt.ll

# compile optimized LLVM IR to assembly
$(binDir)/%.s: $(binDir)/%.opt.ll $(passRuntimes)
	clang++ -S $< $(passRuntimes) -o $@ $(linkLibraries)
.PRECIOUS: $(binDir)/%.s

# compile to optimized LLVM IR to executable
$(binDir)/%.out: $(binDir)/%.opt.ll $(passRuntimes)
	clang++ -fuse-ld=lld $< $(passRuntimes) -o $@ $(linkLibraries)
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
	rm -f $(outputs)
.PHONY: clean

misc:
	@echo $(passes)
	@echo $(passRuntimes)
	@echo $(passLibraryArgs)
	@echo $(binDir)
