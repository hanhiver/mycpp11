#include <iostream>
#include <thread>
#include <queue>

#include "event.hpp"

Event event;
std::queue<int> que;
std::mutex mu;

void produce()
{
    std::cout << "produce" << std::endl;
    do
    {
        std::lock_guard<std::mutex> lock(mu);
        que.push(std::rand());
    }
    while (false);
    event.NotifyOne();
    std::cout << "produce end" << std::endl;
}

void consume()
{
    std::cout << "consume" << std::endl;
    event.Wait();
    std::unique_lock<std::mutex> lock(mu);
    auto t = que.front();
    que.pop();
    std::cout << "consume end" << std::endl;
}

int main()
{
    auto th = std::thread(consume);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread(produce).join();
    th.join();
    return 0;
}