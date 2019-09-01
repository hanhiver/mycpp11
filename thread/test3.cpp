#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

const int N = 10000000;
int num(0);
mutex m;

void run()
{
    for (int i=0; i<N; i++)
    {
        m.lock();
        num++;
        m.unlock();
    }
}

int main()
{
    clock_t start = clock();
    thread t1(run);
    thread t2(run);

    t1.join();
    t2.join();

    clock_t end = clock();

    cout<<"[MUTEX]  num = "<<num<<" runtime: "<<end-start<<endl;
    return 0;
}

