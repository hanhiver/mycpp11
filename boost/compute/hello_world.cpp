#include <iostream> 
#include <boost/compute/core.hpp>

namespace compute = boost::compute;

int main()
{
    // get default devices. 
    compute::device dev = compute::system::default_device();

    // Print the device's name and platform. 
    std::cout << "Hello from " << dev.name()
              << " (platform: " << dev.platform().name() << ")" 
              << std::endl; 
    
    return EXIT_SUCCESS;
}
