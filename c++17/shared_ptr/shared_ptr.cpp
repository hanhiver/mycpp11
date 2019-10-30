#include <iostream> 
#include <memory> 
#include <string> 

class Foo
{
public: 
    std::string name; 

    Foo(std::string n) : name {std::move(n)}
    {
        std::cout << "CTOR: " << name << std::endl; 
    }

    ~Foo()
    {
        std::cout << "DTOR: " << name << std::endl; 
    }
};

void f(std::shared_ptr<Foo> sp)
{
    std::cout << "f() use conter at: " << sp.use_count() << std::endl; 
}

int main()
{
    std::shared_ptr<Foo> fa; 

    {
        std::cout << "Inner scope begin: \n";

        std::shared_ptr<Foo> f1 {new Foo{"foo"}};
        auto f2 (std::make_shared<Foo>("bar"));

        std::cout << "f1's use counter at: " << f1.use_count() << std::endl; 
        fa = f1; 
        std::cout << "f2's use counter at: " << f2.use_count() << std::endl; 
    }

    std::cout << "Back to outer scope. \n";
    std::cout << "fa's use counter at: " << fa.use_count() << std::endl; 

    std::cout << "first f() call\n";
    f(fa);
    std::cout << "second f() call\n";
    f(std::move(fa));

    std::cout << "End of main(). " << std::endl;
}