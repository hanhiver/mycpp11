#include <iostream> 
#include <memory> 
#include <string> 

class Foo
{
public:
    std::string name;

    Foo(std::string n) : name { std::move(n) }
    {
        std::cout << "CTOR: " << name << std::endl; 
    } 

    ~Foo()
    {
        std::cout << "DTOR: " << name << std::endl; 
    }
};

void process_item(std::unique_ptr<Foo> p)
{
    if (!p)
    {
        return; 
    }

    std::cout << "Processing: " << p->name << std::endl; 
}

int main()
{
    // 离开下面程序块的时候，p1和p2都会被自动销毁。
    {
        std::unique_ptr<Foo> p1 {new Foo {"foo"}};
        auto p2 (std::make_unique<Foo>("bar"));
    }

    // 结束process_item函数之后，内部构造的foo1会立刻被销毁。
    process_item(std::make_unique<Foo>("foo1"));

    auto p1 (std::make_unique<Foo>("foo2"));

    // p2会在程序结束的最后被自动销毁。 
    auto p2 (std::make_unique<Foo>("foo3"));

    // 使用std::move，在函数结束的时候，p1被立刻销毁。
    process_item(std::move(p1)); 

    std::cout << "All Done. " << std::endl; 
}