buildDir := build
testDir := src/test
buildSystem := ninja
ifeq ($(buildSystem),ninja)
buildSystemGenerated := Ninja
else
buildSystemGenerated := Unix Makefiles
endif
buildType := Release

cmakeFiles := $(shell find src/cmake -name "*.cmake")

all: build

cmake: CMakeLists.txt $(cmakeFiles)
	cmake -B $(buildDir) -G "$(buildSystemGenerated)" \
	-DCMAKE_BUILD_TYPE=$(buildType)
.PHONY: cmake

passes: cmake
	cd $(buildDir) && $(buildSystem) pass.coverage.branch pass.coverage.block
.PHONY: passes

runtimes: cmake
	cd $(buildDir) && $(buildSystem) runtime.coverage.branch runtime.coverage.block
.PHONY: runtimes

passes.runtimes: cmake
	cd $(buildDir) && $(buildSystem) pass.coverage.branch pass.coverage.block runtime.coverage.branch runtime.coverage.block
.PHONY: passes.runtimes

build: passes
	cd $(buildDir) && $(buildSystem)
.PHONY: build

tests: passes.runtimes $(testDir)/Makefile
	cd $(testDir) && make -r
.PHONY: tests

cleanCmake:
	cd $(buildDir) && $(buildSystem) clean
.PHONY: cleanCmake

cleanTests:
	cd $(testDir) && make -r clean
.PHONY: cleanTests

clean: cleanCmake cleanTests

fullClean:
	rm -rf $(buildDir)
.PHONY: fullClean
