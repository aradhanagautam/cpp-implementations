#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

int stage = 0;
mutex mtx;
condition_variable cv;
void first()
{
    unique_lock<mutex> lock(mtx);
    cout << "first" << endl;
    stage++;
    cv.notify_all();
}
void second()
{
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []
            { return stage == 1; });
    cout << "second" << endl;
    stage++;
    cv.notify_all();
}
void third()
{
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []
            { return stage == 2; });
    cout << "third" << endl;
    stage++;
}
int main()
{
    thread t1(first);
    thread t2(second);
    thread t3(third);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}