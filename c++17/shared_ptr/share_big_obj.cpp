// 有的时候对于大型的数据结构，我们可以通过共享其中内部的某一部分的方式节省开销。
// 对于shared_ptr，共享大型结构中的某一部分变得很方便，只需要共享出其中一部分，整个结构都会被shared_ptr自动管理。
#include <iostream> 
#include <memory> 
#include <string> 

struct person
{
    std::string name; 
    size_t age; 

    person(std::string n, size_t a) : name {std::move(n)}, age {a}
    {
        std::cout << "CTOR: " << name << std::endl; 
    }

    ~person()
    {
        std::cout << "DTOR: " << name << std::endl; 
    }
}; 

int main()
{
    std::shared_ptr<std::string> shared_name; 
    std::shared_ptr<size_t> shared_age; 

    {
        auto sperson (std::make_shared<person>("John Doe", 30)); 

        // shared_ptr的特定构造函数，接受一个共享指针和共享指针持有对象的变量。 
        // 这样就能对整个对象进行管理，但是不用指向他本身。
        shared_name = std::shared_ptr<std::string>(sperson, &sperson->name);
        shared_age = std::shared_ptr<size_t>(sperson, &sperson->age); 
    }

    std::cout << "name: " << *shared_name
              << "\nage: " << *shared_age << std::endl;
}