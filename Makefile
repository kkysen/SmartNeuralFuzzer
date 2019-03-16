buildDir := build
testDir := src/test
buildSystem := Ninja

cmakeFiles := $(shell find src/cmake -name "*.cmake")

all: build

cmake: CMakeLists.txt $(cmakeFiles)
	cmake -B $(buildDir) -G "$(buildSystem)"
.PHONY: cmake

build: cmake
	cd $(buildDir); ninja
.PHONY: build

tests: build $(testDir)/Makefile
	cd $(testDir); make
.PHONY: test

cleanCmake:
	cd $(buildDir); ninja clean
.PHONY: cleanCmake

cleanTests:
	cd $(testDir); make clean
.PHONY: cleanTests

clean: cleanCmake cleanTests
