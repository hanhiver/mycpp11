#include <iostream>
#include <future>
#include <thread> 
#include <vector>
#include <mutex>
using namespace std;

vector<int> allNum; 
mutex lk;

int prepVect(int num)
{
    for (int i = 1; i<=num; ++i)
    {
        allNum.push_back(i);
    }

    return 0;
}

int worker(int filterN)
{
    for (int i=filterN; i<=allNum.size(); i+=filterN)
    {   
        if (allNum[i] == 0)
        {
            continue; 
        }

        lk.lock();
        allNum[i] = 0;
        lk.unlock(); 
    }

    return 0;
}

int main(int argc, char* argv[])
{
    int num;
    cout << "Please enter the value: ";

    try
    {
        cin >> num; 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    prepVect(num);

    vector<future<int>> threadVect; 

    for (int i=2; i<num/2; ++i)
    {
        future<int> result = async(launch::async, worker, i);
        threadVect.push_back(move(result));
    }

    for (auto& elem : threadVect)
    {
        elem.get();
    }
    
    for (auto elem : allNum)
    {
        if (elem > 0)
        {
            cout << elem << " ";
        }
    }

    cout << endl; 
    cout << "Done!" << endl;
}
