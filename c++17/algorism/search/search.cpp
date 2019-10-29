#include <iostream> 
#include <string> 
#include <algorithm> 
#include <iterator> 
#include <functional> 

template <typename Itr> 
static void print(Itr it, size_t chars)
{
    std::copy_n(it, chars, std::ostream_iterator<char>{std::cout}); 
    std::cout << std::endl; 
}

int main()
{
    const std::string long_string {
        "Lorem ipsum dolor sit amet, consetetur"
        " sadipscing elitr, sed diam nonumy eirmod"};
    const std::string needle {"elitr"}; 

    // the old std::search style. 
    {
        auto match(std::search(std::begin(long_string), std::end(long_string), 
                               std::begin(needle), std::end(needle)));
        print(match, 5);
    }   

    // c++17 code, build a std::default_seacher to do the search. 
    {
        auto dscher (std::default_searcher(std::begin(needle), std::end(needle)));
        auto match (std::search(std::begin(long_string), std::end(long_string), dscher));
        print(match, 5);
    }

    // c++17 code. With the default search, we can easily to change the alogrithm. 
    {
        auto bm_seacher (std::boyer_moore_searcher(std::begin(needle), std::end(needle)));
        auto match (std::search(std::begin(long_string), std::end(long_string), bm_seacher));
        print(match, 5); 
    }
    {
        auto bmh_seacher (std::boyer_moore_horspool_searcher(std::begin(needle), std::end(needle)));
        auto match (std::search(std::begin(long_string), std::end(long_string), bmh_seacher));
        print(match, 5); 
    }

}