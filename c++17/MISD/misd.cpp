#include <iostream> 

template <typename ... Ts> 
static auto multicall(Ts ... functions)
{
    return [=](auto x)
    {
        (void) std::initializer_list<int> { ((void) functions(x), 0) ... }; 
    };
}

/* ===== bad example ======= //
auto for_each([](auto f, auto ...xs) 
            {
                return std::initializer_list<int> { f(xs) ... };
            });
// ===== bad example ======= */
// Why we don't use the bad example. 
// 1. Use the return values of the f(xs) to construct a initialize list, but we don't care the return value. 
// 2. We just want to call the functions, we don't need any return value. 
// 3. f could be a function and not return anything, it will be "optimized" by the compiler. 

template <typename F, typename ... Ts> 
static auto for_each(F f, Ts ... xs)
{
    // Thus, here we force to transfer the f(xs) return value to void. 
    // And uses (f(xs), 0).. to let program abandent the return value but put 0 to the initialize list. 
    (void) std::initializer_list<int> { ((void) f(xs), 0)... };
}

static auto brace_print(char a, char b)
{
    return [=] (auto x) 
    {
        std::cout << a << x << b << ", ";
    };
}

int main()
{
    auto f(brace_print('(', ')'));
    auto g(brace_print('[', ']'));
    auto h(brace_print('{', '}'));
    auto nl( [](auto) 
    {
        std::cout << std::endl; 
    });

    auto call_fgh(multicall(f, g, h, nl));
    for_each(call_fgh, 1, 2, 3, 4, 5);
}