#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

const int N = 10000000;
atomic_int num{ 0 };

void run()
{
    for (int i=0; i<N; i++)
    {
        num++;
    }
}

int main()
{
    cout << "=== Single Thread ===" << endl; 
    clock_t start = clock();
    thread t(run);
    t.join();
    clock_t end = clock();

    cout<<"[ATOMIC] num = "<<num<<" runtime: "<<end-start<<endl;

    cout << "\n=== Two Threads ===" << endl; 
    start = clock();
    thread t1(run);
    thread t2(run);
    t1.join();
    t2.join();
    end = clock();

    cout<<"[ATOMIC] num = "<<num<<" runtime: "<<end-start<<endl;

    return 0;
}

