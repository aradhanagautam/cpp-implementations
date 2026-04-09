#include <iostream>
using namespace std;
template <typename T>
class myVector{
    T* arr;
    int sz;
    int cap;

    void resize()
    {
        cap = cap * 2;

        T* newarr = new T[cap];
        for(int i=0;i<sz;i++)
            newarr[i] = arr[i];

        delete[] arr;
        arr = newarr;
    }
public:
    myVector()
    {
        sz=0;
        cap=1;
        arr = new T[cap];
    }
    void push_back(int val)
    {
        if(sz==cap)
            resize();
        arr[sz++] = val;
    }
    void pop_back()
    {
        if(sz>0)
            sz--;
    }
    T& operator[](int index)
    {
        return arr[index];
    }
    int size()
    {
        return sz;
    }
    int capacity()
    {
        return cap;
    }
    ~myVector()
    {
        delete[] arr;
    }
};
int main() {
    myVector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }

    cout << "\nSize: " << v.size();
    cout << "\nCapacity: " << v.capacity();

    return 0;
}
