buildDir := build
testDir := src/test
buildSystem := ninja
ifeq ($(buildSystem),ninja)
buildSystemGenerated := Ninja
else
buildSystemGenerated := Unix Makefiles
endif
buildType := Debug

cmakeFiles := $(shell find src/cmake -name "*.cmake")

all: build

cmake: CMakeLists.txt $(cmakeFiles)
	cmake -B $(buildDir) -G "$(buildSystemGenerated)" \
	-DCMAKE_BUILD_TYPE=$(buildType)
.PHONY: cmake

pass: cmake
	cd $(buildDir) && $(buildSystem) pass
.PHONY: pass

runtime: cmake
	cd $(buildDir) && $(buildSystem) runtime
.PHONY: runtime

main: cmake
	cd $(buildDir) && $(buildSystem) main
.PHONY: main

test: main
	cd $(buildDir) && $(buildSystem) test
.PHONY: test

build: test

.PHONY: build

tests: main $(testDir)/Makefile
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
