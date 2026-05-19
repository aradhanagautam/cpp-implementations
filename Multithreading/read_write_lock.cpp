#include <iostream>
#include <thread>
#include <mutex>
#include<vector>

using namespace std;

class ReadWriteLock {
private:
    int read_count = 0;
    mutex read_count_mtx;
    mutex resource_mtx;
public:
    void lock_read()
    {
        lock_guard<mutex> lock(read_count_mtx);
        read_count++;
        if(read_count == 1)
            resource_mtx.lock();
    }
    void unlock_read()
    {
        lock_guard<mutex> lock(read_count_mtx);
        read_count--;
        if(read_count == 0)
            resource_mtx.unlock();
    }
    void lock_write()
    {
        resource_mtx.lock();
    }
    void unlock_write()
    {
        resource_mtx.unlock();
    }

};