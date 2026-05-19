#include <iostream>

using namespace std;
template<typename T>

class sharedptr{
T* ptr;
int* ref_count;
public:
sharedptr(T* p)
{
	ptr = p;
	ref_count = new int(1);
    cout << "Constructor called, ref_count: " << *ref_count << endl;
}
~sharedptr()
{
    if(ref_count == nullptr) return;
	(*ref_count)--;
	if(*ref_count == 0)
	{
		delete ptr;
		delete ref_count;
	}
    cout << "Destructor called, ref_count: " << (ref_count ? *ref_count : 0) << endl;
}
sharedptr(const sharedptr& other)
{
    if(other.ref_count == nullptr) return;
	ptr = other.ptr;
	ref_count = other.ref_count;
	(*ref_count)++;
    cout << "Copy constructor called, ref_count: " << *ref_count << endl;
}
sharedptr& operator=(const sharedptr& other)
{
	if(this != &other)
	{
	(*ref_count)--;
	if(*ref_count == 0)
	{
		delete ptr;
		delete ref_count;
	}
	ptr = other.ptr;
	ref_count = other.ref_count;
	 (*ref_count)++;
	}
    cout << "Copy assignment called, ref_count: " << (ref_count ? *ref_count : 0) << endl;
	return *this;
}
sharedptr(sharedptr&& other)
{
	ptr = other.ptr;
	ref_count = other.ref_count;
	other.ptr = nullptr;
	other.ref_count = nullptr;
    cout << "Move constructor called, ref_count: " << (ref_count ? *ref_count : 0) << endl;
}
sharedptr& operator=(sharedptr&& other)
{
	if(this != &other)
	{
	(*ref_count)--;
	if(*ref_count == 0)
	{
		delete ptr;
		delete ref_count;
	}
	ptr = other.ptr;
	ref_count = other.ref_count;
	other.ptr = nullptr;
	other.ref_count = nullptr;
    cout << "Move assignment called, ref_count: " << (ref_count ? *ref_count : 0) << endl;
	}
	return *this;
}
T* operator->()
{
	return ptr;
}
T& operator*()
{
	return *ptr;
}
};
int main()
{
sharedptr<int> p1(new int(10));
sharedptr<int> p2(new int(10));
sharedptr<int> p3 = p1;
p2= p3;
sharedptr<int> p4 = move(p1);
p3 = move(p4);
}