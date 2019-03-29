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
#	-DCMAKE_LINKER=ld.lld -DCMAKE_CXX_LINK_EXECUTABLE="<CMAKE_LINKER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>"
.PHONY: cmake

build: cmake
ifeq ($(buildSystem),ninja)
	cd $(buildDir) && $(buildSystem) pass.coverage.branch pass.coverage.block && $(buildSystem)
else
    cd $(buildDir) && $(buildSystem)
endif
.PHONY: build

tests: build $(testDir)/Makefile
	cd $(testDir) && make -r
.PHONY: test

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
