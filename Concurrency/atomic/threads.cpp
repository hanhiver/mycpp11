#include <iostream> 
#include <thread> 
#include <vector> 
#include <string> 

void sayHello(std::string str, int& num)
{
    std::cout << "Hello, " << str << ", thread id: " << std::this_thread::get_id() << std::endl;
    ++ num; 
}

int main()
{
    /*
    std::thread th1(sayHello);
    std::thread th2(sayHello);
    th1.join();
    th2.join();
    */
    int num = 0;
    std::vector<std::thread> threads; 
    for (int i=0; i<20; ++i)
    {
        std::thread th(sayHello, "dhan", std::ref(num));
        threads.push_back(std::move(th));
    }

    for (auto& th : threads)
    {
        th.join();
    }

    std::cout << "Num: " << num << std::endl;

}