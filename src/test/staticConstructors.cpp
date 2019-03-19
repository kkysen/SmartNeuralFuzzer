//
// Created by Khyber on 3/18/2019.
//

class A {

public:
    
    static bool initialized;
    
    A() noexcept {
        initialized = true;
    }
    
    ~A() {
        initialized = false;
    }
    
};

bool A::initialized = false;

A a;

int main() {
    return static_cast<int>(A::initialized);
}
