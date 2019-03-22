coveragePasses := branch
#block
passes := $(coveragePasses:%=coverage.%)

tests := branch switch optimizedSwitch loop virtualCall staticConstructors

srcDir := .
projectDir := ../..
buildDir := $(projectDir)/build
binDir := $(buildDir)/test

passLibraries := $(passes:%=$(buildDir)/src/main/pass/libpass.%.so)
passRuntimes := $(passes:%=$(buildDir)/src/main/runtime/libruntime.%.a)

passLibraryArgs := $(passLibraries:%=-load=%)
passArgs := $(passes:%=-%)

flags := -S -emit-llvm -flto -fwhole-program-vtables
linkLibraries := -lstdc++fs


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
$(binDir)/%.s: $(binDir)/%.opt.ll $(passRuntimes)
	clang++ -S $< $(passRuntimes) -o $@ $(linkLibraries)
.PRECIOUS: $(binDir)/%.s

# compile to optimized LLVM IR to executable
$(binDir)/%.out: $(binDir)/%.opt.ll $(passRuntimes)
	clang++ $< $(passRuntimes) -o $@ $(linkLibraries)
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
	@echo $(passes)
