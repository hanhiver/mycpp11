#include <iostream> 
#include <boost/circular_buffer.hpp>

int main()
{
    boost::circular_buffer<int> cb(3);

    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(4);

    int a = cb[0];
    int b = cb[1];
    int c = cb[2];
    std::cout << a << b << c << std::endl;

    cb.push_back(5);
    cb.push_back(8);

    a = cb[0];
    b = cb[1];
    c = cb[2];
    std::cout << a << b << c << std::endl;

    cb.pop_back();
    cb.pop_front();

    for (auto item : cb)
    {
        std::cout << item; 
    }
    std::cout << std::endl;

    return 0;
}