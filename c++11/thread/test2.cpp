#include <iostream>
#include <thread>

using namespace std;

const int N = 10000000;
int num = 0;

void run()
{
    for (int i=0; i<N; i++)
    {
        num++;
    }
}

int main()
{
    clock_t start = clock();
    thread t1(run);
    t1.join();

    thread t2(run);
    t2.join();

    clock_t end = clock();

    cout<<"[SERIAL] num = "<<num<<" runtime: "<<end-start<<endl;
    return 0;
}

