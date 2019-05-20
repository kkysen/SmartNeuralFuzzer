passes := block branch

tests := branch switch optimizedSwitch argcLoop nLoop virtualCall staticConstructors

srcDir := .
projectDir := ../..
buildDir := $(projectDir)/build
binDir := $(buildDir)/test

ldPreloadLibraries := $(buildDir)/src/main/pass/register/libpass.register.so

passLibraries := $(shell ./find.sh pass.so $(buildDir) $(passes))
passRuntimes := $(shell ./find.sh runtime.a $(buildDir) $(passes))

passLibraryArgs := $(passLibraries:%=-load=%)
#passArgs := $(passes:%=-coverage.%)

preOptimization := -O0
concurrentOptimization := -O3
postOptimization := -O0


flags := $(preOptimization) -S -emit-llvm -flto -fwhole-program-vtables
linkLibraries := -lstdc++fs -lstdc++ # latter needed for clang-9 only for some reason


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
	clang-9 $(flags) $< -o $@
.PRECIOUS: $(binDir)/%.ll

# compile C++ to LLVM IR
$(binDir)/%.ll: $(srcDir)/%.cpp
	mkdir -p $(dir $@)
	clang-9 $(flags) $< -o $@
.PRECIOUS: $(binDir)/%.ll

# instrument LLVM IR
$(binDir)/%.instr.ll: $(binDir)/%.ll $(passLibraries) $(ldPreloadLibraries)
	LD_PRELOAD=$(ldPreloadLibraries) opt-9 $(concurrentOptimization) $(passLibraryArgs) $(passArgs) -S < $< > $@
.PRECIOUS: $(binDir)/%.instr.ll

# optimizize LLVM IR
$(binDir)/%.opt.ll: $(binDir)/%.instr.ll
	opt-9 $(postOptimization) -S < $< > $@
.PRECIOUS: $(binDir)/%.opt.ll

# compile optimized LLVM IR to assembly
$(binDir)/%.s: $(binDir)/%.opt.ll $(passRuntimes)
	clang-9 -S $< $(passRuntimes) -o $@ $(linkLibraries)
.PRECIOUS: $(binDir)/%.s

# compile to optimized LLVM IR to executable
$(binDir)/%.out: $(binDir)/%.opt.ll $(passRuntimes)
	clang-9 -fuse-ld=lld $< $(passRuntimes) -o $@ $(linkLibraries)
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
