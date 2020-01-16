XXX: This only works for boost 1_70_0 or later. 
#include "../common.hpp"

#include <boost/container/vector.hpp>
#include <boost/static_assert.hpp>

//Make sure assertions are active
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>

int main()
{
    using namespace boost::container; 

    // Specifies that a vector that will use "unsigned char" as 
    // the type to store capacity or size internally. 
    typedef vector_options< stored_size<unsigned char> >::type size_option_t; 

    std::cout << "Done. " << std::endl; 
    return EXIT_SUCCESS;
}