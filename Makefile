buildDir := build
testDir := src/test
buildSystem := ninja
buildSystemGenerated := Ninja
buildType := Release

cmakeFiles := $(shell find src/cmake -name "*.cmake")

all: build

cmake: CMakeLists.txt $(cmakeFiles)
	cmake -B $(buildDir) -G "$(buildSystemGenerated)" \
	-DCMAKE_BUILD_TYPE=$(buildType)
#	-DCMAKE_LINKER=ld.lld -DCMAKE_CXX_LINK_EXECUTABLE="<CMAKE_LINKER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>"
.PHONY: cmake

build: cmake
	cd $(buildDir); $(buildSystem)
.PHONY: build

tests: build $(testDir)/Makefile
	cd $(testDir); make -r
.PHONY: test

cleanCmake:
	cd $(buildDir); ninja clean
.PHONY: cleanCmake

cleanTests:
	cd $(testDir); make -r clean
.PHONY: cleanTests

clean: cleanCmake cleanTests

fullClean:
	rm -rf $(buildDir)
.PHONY: fullClean
