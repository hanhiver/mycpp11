#include <iostream> 
#include <vector> 
#include <thread> 

#include "threadsafe_queue.cpp"

#define LOOP_COUNT 10
#define QUEUE_CAPACITY 10

void producer(threadsafe_queue<long>& queue)
{
    for (long i=0; i<LOOP_COUNT; ++i)
    {
        queue.push(i);
    }
}

void consumer(threadsafe_queue<long>& queue)
{
    while (true)
    {
        long elem = 0; 
        bool res = queue.wait_and_pop(elem);
        
        if (res)
        {
            std::cout << "Got: " << elem << std::endl; 
            if (elem = LOOP_COUNT-2 )
            {
                queue.termination();
            }
        }
        else
        {
            break; 
        }
    }
}

int main()
{
    threadsafe_queue<long> queue;

    std::thread th(producer, std::ref(queue));
    consumer(queue);
    th.join();
    return 0;
}