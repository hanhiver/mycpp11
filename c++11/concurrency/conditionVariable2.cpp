#include <condition_variable>
#include <mutex> 
#include <future> 
#include <thread> 
#include <iostream>
#include <queue>

std::queue<int> queue;
std::mutex queueMutex;
std::condition_variable queueCondVar;

void provider(int val)
{
    // push different values. 
    for(int i=0; i<6; ++i)
    {
        {
            std::lock_guard<std::mutex> log(queueMutex);
            queue.push(val + i);
        } // release lock queueMutex. 
        queueCondVar.notify_one();

        std::this_thread::sleep_for(std::chrono::milliseconds(val));
    }
}

void consumer(int num)
{
    // pop value if available. 
    while (true)
    {
        int val;
        {
            std::unique_lock<std::mutex> ul(queueMutex);
            queueCondVar.wait(ul, []{ return !queue.empty(); });
            val = queue.front();
            queue.pop();
        } // release lock ul. 

        std::cout << "Consumer " << num << ": " << val << std::endl; 
    }
}

int main()
{
    // start three providers for values 100+, 300+ and 500+
    auto p1 = std::async(std::launch::async, provider, 100);
    auto p2 = std::async(std::launch::async, provider, 300);
    auto p3 = std::async(std::launch::async, provider, 500);

    // start two consumers printing the values. 
    auto c1 = std::async(std::launch::async, consumer, 1);
    auto c2 = std::async(std::launch::async, consumer, 2);
}
