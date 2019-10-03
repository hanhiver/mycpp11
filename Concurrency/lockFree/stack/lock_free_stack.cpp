#include <atomic> 
#include <memory>

template<typename T> 
class lock_free_stack
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        node* next; 

        node(T const& data_):
            data(std::make_shared<T>(data_))
        {}
    };
    std::atomic<node*> head; 
    std::atomic<unsigned> threads_in_pop;
    std::atomic<node*> to_be_deleted;

    static void delete_nodes(node* nodes)
    {
        // 顺着nodes链条，将所有的每一个节点删除。
        while(nodes)
        {
            node* next = nodes->next; 
            delete nodes;
            nodes = next; 
        }
    } 

    void chain_pending_nodes(node* nodes)
    {
        node* last = nodes;
        // 顺着last节点不断往下找，知道找到节点链条最后的节点，赋值给last。
        while (node* const next = last->next)
        {
            last = next; 
        }
        // 将从nodes到last的一串nodes都串联到to_be_deleted链上。
        chain_pending_nodes(nodes, last);
    }

    void chain_pending_nodes(node* first, node* last)
    {
        // 把传入的链条最后一个节点连接上to_be_deleted链条。
        last->next = to_be_deleted;
        // (1)通过原子操作比对to_be_deleted和传入nodes的最后一个节点。
        // 如果两者相同，赋值传入链条的第一个节点到to_be_deleted，完成链接工作。
        // 如果两者不同，意味着还有其他线程又插入了nodes到to_be_deleted链条中，
        //    将to_be_deleted的新值赋给last->next，继续到(1)进行循环。
        while (!to_be_deleted.compare_exchange_weak(last->next, first));
    }

    void chain_pending_node(node* n)
    {
        chain_pending_nodes(n, n);
    }

    void try_reclaim(node* old_head)
    {
        if (threads_in_pop == 1) // 我是进入pop的唯一线程。
        {
            // 将所to_be_deleted链条上的nodes放到nodes_to_delete里面，同时清空to_be_delete链条。
            node* nodes_to_delete = to_be_deleted.exchange(nullptr);
            // 减少一个在pop中的线程数，判断减少之后是否为零即我还是进入pop的唯一线程么？
            if (!--threads_in_pop) 
            {
                // 如果是，安全的删除所有需要删除的节点。
                delete_nodes(nodes_to_delete);
            }
            else if(nodes_to_delete)
            {
                // 如果不是，说明有其他线程进入了pop函数。
                // 判断是否已经有线程又插入了节点在等待需要删除的节点列表里。
                // 如果已经有插入节点在列表里，将nodes_to_delete串接到to_be_deleted链条上。
                chain_pending_nodes(nodes_to_delete);
            }
            // 安全删除old_head.
            delete old_head;
        }
        else
        {
            // 我不是唯一进入pop的线程，将需要删除的old_head放入to_be_delete连接。
            chain_pending_node(old_head);
            // 减少一个在pop中的线程数，退出try_reclaim. 
            --threads_in_pop;
        }
    }

public:
    void push(T const& data)
    {
        node* const new_node = new node(data);
        new_node->next = head.load();
        // (1)这里用原子操作查看head是否等于new_node->next。
        // 如果相等，则将new_node的值赋给head，函数返回true，循环退出。
        // 如果不相等，表明可能其他线程修改了head的值，则将head的新值赋给new_node->next，函数返回false，回到(1)继续循环。
        // compare_exchange_weak有时候可能会出现假的false判断，如果这种情况出现，会再有一轮重新判断。
        while(!head.compare_exchange_weak(new_node->next, new_node));
    }

    std::shared_ptr<T> pop()
    {
        // 进入pop()的时候自增，表示当前多少线程在pop()中。
        ++threads_in_pop;
        node* old_head = head.load();
        // 首先要判断head是否指向了空指针，也就是空的栈。
        // (1) 用原子操作比对head和old_head的值，如果相等，则将old_head->next赋值给head，新的head赋值完成。
        // 如果不相等，则有可能其他的节点插入或者删除导致head节点变化，将head的新值赋给old_head，回到(1)继续循环。
        while ( old_head &&
                !head.compare_exchange_weak(old_head, old_head->next));
        // 生成一个临时变量，用来返回pop出来的值。
        std::shared_ptr<T> res;
        if (old_head)
        {
            // 如果old_head不为空，用swap的方式将其中的data转移到res里面。
            res.swap(old_head->data);
        }
        // 尝试删除节点。
        try_reclaim(old_head);
        return res; 
    }
};