#include <iostream>
#include <thread>
#include <mutex>
#include<vector>
#include<shared_mutex>
using namespace std;

int read_count = 0;
shared_mutex resource_mtx;
mutex cout_mtx;

int buffer=0;

void reader(int id)
{
    shared_lock<shared_mutex> lock(resource_mtx);
{
    lock_guard<mutex> lock(cout_mtx);
    cout << "Reader " << id << " reads: " << buffer << endl;
}
}
void writer(int id)
{
    unique_lock <shared_mutex> lock(resource_mtx);
    buffer++;
{
    lock_guard<mutex> lock(cout_mtx);
    cout << "Writer " << id << " wrote: " << buffer << endl;
}
}
int main()
{
    vector<thread> readers;
    vector<thread> writers;

    for (int i = 0; i < 2; i++)
    {
        writers.emplace_back(writer, i + 1);
    }
    for (int i = 0; i < 3; i++)
    {
        readers.emplace_back(reader, i + 1);
    }


    for (auto& t : readers)
    {
        t.join();
    }
    for (auto& t : writers)
    {
        t.join();
    }
}