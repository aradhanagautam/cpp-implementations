#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::mutex mtx;
std::condition_variable cv;

int current = 1;
bool oddTurn = true;

void odd()
{
    while (true)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return oddTurn || current > 20; });
        if (current > 20)
            break;
        cout << current << " ";
        current++;
        oddTurn = false;
        cv.notify_one();
    }
}
void even()
{
    while (true)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !oddTurn || current > 20; });
        if (current > 20)
            break;
        cout << current << " ";
        current++;
        oddTurn = true;
        cv.notify_one();
    }
}
int main()
{
    thread t1(odd);
    thread t2(even);

    t1.join();
    t2.join();
    return 0;
}
