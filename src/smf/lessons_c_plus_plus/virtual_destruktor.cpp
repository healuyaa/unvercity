#include <iostream>

class A {
public:
    A() {
        std::cout << "new dynamic memory, object A" << std::endl;
    }
    virtual ~A() {
        std::cout << "delete dynamic memory, object A" << std::endl;
    }
};

class B : public A {
public:
    B() {
        std::cout << "new dynamic memory, object B" << std::endl;
    }
    ~B() override {
        std::cout << "delete dynamic memory, object B" << std::endl;
    }
};

class C {
public:
    C() {}
    virtual ~C() = 0;
};

C::~C() {};

class D : public C {
public:
    D() {
        
    }
    ~D() override {
        
    }
};

int main() {
    A *bptr = new B;
    delete bptr;

    C *bptr = new D;
    delete bptr;
}