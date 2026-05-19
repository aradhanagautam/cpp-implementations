#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

using namespace std;

const int capacity = 10;

queue<int> buffer;
mutex mtx;
condition_variable producer_cv;
condition_variable consumer_cv;

void producer()
{
    for (int i = 0; i < 10; i++)
    {
        unique_lock<mutex> lock(mtx);
        producer_cv.wait(lock, []
                { return buffer.size() < capacity; });
        buffer.push(i);
        cout << "Produced: " << buffer.back() << endl;
        consumer_cv.notify_one();
    }
}
void consumer()
{
    for (int i = 0; i < 10; i++)
    {
        unique_lock<mutex> lock(mtx);
        consumer_cv.wait(lock, []
                { return buffer.size() > 0; });
        cout << "consumed: " << buffer.front() << endl;
        buffer.pop();
        producer_cv.notify_one();
    }
}
int main()
{
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();
    return 0;
}