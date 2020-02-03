#include <iostream> 
#include <vector> 
#include <boost/signals2.hpp>

float product(float x, float y) { return x*y; }
float quotient(float x, float y) { return x/y; }
float sum(float x, float y) { return x+y; }
float difference(float x, float y) { return x-y; }

template <typename T> 
struct maximum
{
    // result_type must be define here in order to tell the lib 
    // exactly result type of the fuctions. 
    typedef T result_type; 
    
    template<typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const 
    {
        if (first == last)
        {
            return T();
        }

        T max_value = *first++;
        
        while(first != last)
        {
            if (max_value < *first)
            {
                max_value = *first; 
            }
            ++ first; 
        }

        return max_value;
    }
};

template <typename Container>
struct aggregate_values
{
    typedef Container result_type; 

    template <typename InputIter> 
    Container operator()(InputIter first, InputIter last) const 
    {
        Container values; 

        while(first != last)
        {
            values.push_back(*first);
            ++ first; 
        }

        return values; 
    }
};

int main()
{
    boost::signals2::signal<float (float, float), maximum<float> > sig; 

    sig.connect(&product);
    sig.connect(&quotient);
    sig.connect(&sum);
    sig.connect(&difference);

    std::cout << "Max: " << sig(5, 3) << std::endl; 

    boost::signals2::signal<float (float, float), aggregate_values<std::vector<float>>> sig2; 
    
    sig2.connect(&product);
    sig2.connect(&quotient);
    sig2.connect(&sum);
    sig2.connect(&difference);

    for(auto& item : sig2(3, 4))
    {
        std::cout << item << ", ";
    }
    std::cout << std::endl; 

    return EXIT_SUCCESS;
}