#include <iostream> 
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>


using namespace boost::accumulators;

int main()
{
    accumulator_set<double, stats<tag::mean, tag::moment<2> > > acc; 

    acc(1.2);
    acc(2.3);
    acc(3.4);
    acc(4.5);

    std::cout << "Count:     " << count(acc) << std::endl; 
    std::cout << "Mean:      " << mean(acc) << std::endl; 
    std::cout << "Moment:    " << moment<2>(acc) << std::endl; 
}
