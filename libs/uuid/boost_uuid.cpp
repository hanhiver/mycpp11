#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <string> 
#include <iostream> 

int main()
{
    boost::uuids::random_generator gen;
    boost::uuids::uuid id = gen();

    std::string s = to_string(id);
    std::cout << s << std::endl;

    //std::cout << boost::uuids::lexical_cast<std::string>(id) << std::endl;

    return 0;
}
