#include <iostream>
using namespace std;
template <typename T>

class SmartPtr{
 T* ptr;
public:
//constructor
 SmartPtr(T* p)
 {
    ptr = p;
 }

SmartPtr(const SmartPtr&) = delete; // delete copy constructor for unique ownership
SmartPtr& operator=(const SmartPtr&) = delete; // delete assignment operator for unique ownership

 
// Move Constructor
SmartPtr(SmartPtr&& other) {
    cout << "Move Constructor\n";
    ptr = other.ptr;
    other.ptr = nullptr;
}

// Move Assignment 
SmartPtr& operator=(SmartPtr&& other) {
    cout << "Move Assignment\n";
    if (this != &other) {
        delete ptr;            // clean current resource
        ptr = other.ptr;       // steal
        other.ptr = nullptr;   // empty source
    }
    return *this;
}
//operator overloading so that we can do *obj and get the value stored at pointer
T& operator*()
{
    return *ptr;
}
//operator overloading so that we can do 0bj->func()
T* operator->()
{
    return ptr;
}
// Helper
T* get() {
    return ptr;
}
//destructor
 ~SmartPtr()
 {
    delete ptr;
 }
};
class Test{
    public:
    Test() { cout << "Constructor\n"; }
    ~Test() { cout << "Destructor\n"; }

    void sayHello() {
        cout << "Hello from Test\n";
    }
};
int main()
{
    SmartPtr<Test> sp1(new Test());
    sp1->sayHello();

    SmartPtr<Test> sp2 = std::move(sp1);

    if (sp1.get() == nullptr)
        cout << "sp1 is now null after move\n";
    sp2->sayHello();

    cout << "\n---- Move Assignment ----\n";
    SmartPtr<Test> sp3(new Test());
    sp3 = std::move(sp2);

    if (sp2.get() == nullptr)
        cout << "sp2 is now null after move\n";

    sp3->sayHello();

}