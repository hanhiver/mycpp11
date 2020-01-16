#include <iostream> 

#include <boost/container/vector.hpp>
#include <boost/container/stable_vector.hpp>
#include <boost/container/deque.hpp>
#include <boost/container/list.hpp>
#include <boost/container/map.hpp>
#include <boost/container/string.hpp>
using namespace boost::container; 

/*
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <string> 
using namespace std; 
*/
struct data
{
    int i_; 

    // a vector holding still undefined class 'data'
    vector<data> v_; 
    vector<data>::iterator vi_; 

    // a stable_vector holding still undifined class 'data'
    //stable_vector<data> sv_;
    //stable_vector<data>::iterator svi_; 

    // a deque holding still undefined class 'data'. 
    deque<data> d_;
    deque<data>::iterator di_;

    // a list holding still undifined class 'data'. 
    list<data> l_; 
    list<data>::iterator li_;

    // a map holding still undified class 'data'. 
    map<data, data> m_;
    map<data, data>::iterator mi_;

    friend bool operator <(const data& l, const data& r)
    {
        return l.i_ < r.i_; 
    }
};

struct tree_node
{
    string name; 
    string value; 
    
    // children nodes of this node. 
    list<tree_node> children_; 
    list<tree_node>::iterator selected_child_; 
};

int main()
{
    // a container holding a recursive data type. 
    //stable_vector<data> sv; 
    vector<data> sv; 
    sv.resize(100);

    // Let's build a tree based in a recursive data type. 
    tree_node root; 
    root.name = "root";
    root.value = "root_value";
    root.children_.resize(7);
    root.selected_child_ = root.children_.begin();

    std::cout << "done!" << std::endl; 
    return 0; 
}