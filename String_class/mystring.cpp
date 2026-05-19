#include <iostream>
#include <cstring>
using namespace std;

class mystring{
    char* data;
    int len;

    public:

    //Default Constructor
    mystring(): data(nullptr),len(0) {}

    //Parameterized Constructor
    mystring(const char* str)
    {
        if(str)
        {
            len = strlen(str);
            data = new char[len+1];
            strcpy(data,str);
        }
        else
        {
            data = nullptr;
            len = 0;
        }
    }

    //Copy Constructor
    mystring(const mystring& other)
    {
        len = other.len;
        data = new char[len+1];
        strcpy(data, other.data);
    }

    //Copy Assignment Operator
    mystring& operator=(const mystring& other)
    {
        if(this != &other)
        {
            delete[] data;
            len = other.len;

            if(other.data)
            {
                data = new char[len+1];
                strcpy(data,other.data);
            }
            else
            {
                data = nullptr;
            }
        }
        return *this;
    }

    //Move Constructor
    mystring(mystring&& other)
    {
        data = other.data;
        len = other.len;
        
        other.data = nullptr;
        other.len = 0;
    }

    //Move Assignment Operator
    mystring& operator=(mystring&& other)
    {
        if(this != &other)
        {
            delete [] data;
            data = other.data;
            len = other.len;

            other.data = nullptr;
            other.len  = 0;
        }
        return *this;
    }
    //To get length
    int length()
    {
        return len;
    }

    //Access Operator
    char& operator[](int index)
    {
        return data[index];
    }

    ~mystring()
    {
        delete [] data;
    }

};
int main()
{
    mystring s1; //Default Constructor
    mystring s2 = "Hello"; //Parameterized Constructor
    mystring s3 = s2; //Copy Constructor
    s1 = s2; //Copy Assignment Operator
    mystring s4 = std::move(s1); //Move Constructor
    s1 = std::move(s2); //Move Assignment Operator
    int sz = s1.length();
    char x = s1[2];

    cout << "Length of s1: " << sz << endl;
    cout << "Character at index 2 of s1: " << x << endl;
    return 0;
}