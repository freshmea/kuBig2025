#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using namespace std;

class TaskQueue
{
private:
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    vector<thread> workers;
    atomic<bool> stop{false};

public:
    TaskQueue(size_t thread_count)
    {
        for (size_t i = 0; i < thread_count; ++i)
        {
            workers.emplace_back([this]()
                                 {
                while(true){
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(mtx);
                        cv.wait(lock, [this]()
                                { return stop || !tasks.empty(); });
                        if (stop &&tasks.empty())
                            return;
                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task(); // task 실행
                } });
        }
    }
};