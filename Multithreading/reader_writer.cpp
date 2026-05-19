#include <iostream>
#include <thread>
#include <mutex>
#include<vector>

using namespace std;

int read_count = 0;
mutex read_count_mtx;
mutex resource_mtx;
mutex cout_mtx;

int buffer=0;

void reader(int id)
{
    {    
        lock_guard<mutex> lock(read_count_mtx);   
        read_count++;
        if (read_count == 1)
            resource_mtx.lock();
    }
    {
        lock_guard<mutex> lock(cout_mtx);
        cout << "Reader " << id << " reads: " << buffer << endl;
    }
    {
        lock_guard<mutex> lock(read_count_mtx);
        read_count--;
        if (read_count == 0)
            resource_mtx.unlock();
    }
}
void writer(int id)
{
    lock_guard<mutex> lock(resource_mtx);
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