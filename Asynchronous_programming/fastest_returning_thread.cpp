#include <future>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

string fetch_data(const string& source, int delay)
{
    std::this_thread::sleep_for(std::chrono::seconds(delay));  // Simulate a long-running task
    cout << "Data fetched from " << source << " after " << delay << " seconds." << endl;
    return source;
}
int main()
{
    vector<future<string>> futures;
    // Start fetching data from two sources concurrently
    future<string> f1 = std::async(std::launch::async, fetch_data, "Source A", 3);
    future<string> f2 = std::async(std::launch::async, fetch_data, "Source B", 5);
    futures.push_back(std::move(f1));
    futures.push_back(std::move(f2));

    // Do other work while waiting for the data to be fetched
    cout << "Doing other work while waiting for data..." << endl;

    bool found = false;
    while (!found)
    {
        for (auto& f : futures)
        {
            if (f.wait_for(std::chrono::seconds(0)) == future_status::ready)
            {
                string result = f.get();  // Get the result from the ready future
                cout << "Source returned first: " << result << endl;
                found = true;
                break;
            }
        }

        if (!found)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return 0;
}

