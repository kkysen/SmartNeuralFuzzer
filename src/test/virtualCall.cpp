#include <cstdio>

class A;

extern "C"
void doVirtualCall(A& a) noexcept;

class A {

public:
    
    virtual char f() noexcept = 0;
    
    virtual long g() noexcept = 0;
    
    void doVirtualCall() noexcept {
        ::doVirtualCall(*this);
    }
	
};

void doVirtualCall(A& a) noexcept {
    printf("%c: %c, %lu\n", 'A', a.f(), a.g());
}

class B : public A {

public:
    
    char f() noexcept override {
        return 'B';
    }
    
    long g() noexcept override {
        return 1;
    }
    
};

class C : public A {

public:
    
    char f() noexcept override {
        return 'C';
    }
    
    long g() noexcept override {
        return 2;
    }
    
};

extern "C"
void testVirtualCall(int argc) {
	B b;
    C c;
    A* array[] = {&b, &c};
    A& a = *array[argc % (sizeof(array) / sizeof(*array))];
    a.doVirtualCall();
}

int main(int argc, [[maybe_unused]] char** argv) {
	testVirtualCall(argc);
	return 0;
}
