#include <iostream>
#include <future>
#include <thread>
using namespace std;

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 10;
    int b = 32;

    cout << "Normall function call: " << endl; 
    cout << "a + b = " << add(a, b) << "\n" << endl;

    cout << "Async fuction call: " << endl; 
    std::future<int> f = std::async(add, a, b);
    cout << "a + b = " << f.get() << "\n" << endl;

    cout << "Packaged task call: " << endl;
    std::packaged_task<int(int, int)> task(add);
    std::future<int> t = task.get_future();
    task(a, b);
    cout << "a + b = " << t.get() << "\n" << endl;

}