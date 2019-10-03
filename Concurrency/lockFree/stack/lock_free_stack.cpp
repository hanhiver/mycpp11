#include <atomic> 

template<typename T> 
class lock_free_stack
{
private:
    struct node
    {
        T data;
        node* next; 

        node(T const& data_):
            data(data_)
        {}
    };
    std::atomic<node*> head; 

public:
    void push(T const& data)
    {
        node* const new_node = new node(data);
        new_node->next = head.load();
        // (1)这里用原子操作查看head是否等于new_node->next。
        // 如果相等，则将new_node的值赋给head，函数返回true，循环退出。
        // 如果不相等，表明可能其他线程修改了head的值，则将head的新值赋给new_node->next，函数返回false，回到(1)继续循环。
        while(!head.compare_exchange_weak(new_node->next, new_node));
    }
};