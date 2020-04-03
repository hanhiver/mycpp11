#include <iostream> 

template <typename T> 
class node
{
public:
    T elem; 
    node* next; 

    node(const T& value):elem(value) {};
};

int main()
{
    node<int>* head = new node<int>(0);
    delete head; 

    std::cout << "Done! " << std::endl; 
    return 0; 
}