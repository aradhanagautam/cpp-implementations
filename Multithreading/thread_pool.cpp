#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
using namespace std;

class threadpool{
private:
	vector<thread> workers;
	queue<function <void()>> tasks;
	mutex mtx;
	condition_variable cv;
	bool stop;
public:
	threadpool(int num_threads)
	{
		stop = false;
		for(int i=0;i<num_threads;i++)
		{
			workers.emplace_back([this]{
		while(true)
		{
			unique_lock<mutex> lock(mtx);
			cv.wait(lock, [this]{return !tasks.empty() || stop;});
			
			if(stop && tasks.empty())
				return;
			
			function<void()> task = tasks.front();
			tasks.pop();
			lock.unlock();
			task();
		}
		});
		}
	}
	void enqueue(function<void()> f)
	{
		{
		unique_lock<mutex> lock(mtx);
		tasks.push(f);
		}
		cv.notify_all();
	}
	~threadpool()
	{
		{
		unique_lock<mutex> lock(mtx);
		stop = true;
		}
		cv.notify_all();
		for(auto& t: workers)
			t.join();
        
        cout << "Thread pool destroyed, all threads joined." << endl;
	}
};
int main()
{
    mutex cout_mtx;
    threadpool pool(4);
    for(int i=0;i<10;i++)
    {
        pool.enqueue([i,&cout_mtx]{
            lock_guard<mutex> lock(cout_mtx);
            cout << "Task " << i << " is being processed by thread " << this_thread::get_id() << endl;
        });
    }
}