#include <chrono>
#include <map> 
#include <memory> 
#include <string> 
#include <thread> 
#include <random> 

#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <prometheus/histogram.h>

int main(int argc, char* argv[])
{
    using namespace prometheus;
    using BucketBoundaries = std::vector< double >;

    // 建立一个在5001端口监听的server。
    Exposer exposer {"0.0.0.0:5001"};

    // 建立一个符合正态分布的随机数生成器。
    std::knuth_b e; 
    std::uniform_real_distribution<double> ud(0.0, 10.0);

    BucketBoundaries bb {2.0, 4.0, 6.0, 8.0};

    // 建立一个metrics registry。 
    auto registry = std::make_shared<Registry>();

    auto& hist_family = BuildHistogram()
                        .Name("normal_distribution")
                        .Help("Histogram of the normal distribution. ")
                        .Labels({{"apps", "dhan"}})
                        .Register(*registry);
    
    // Add a histogram to the metric family. 
    auto& norm_dist = hist_family.Add(
        {{"another_label", "value"}, {"yet_another_label", "value"}}, bb);

    exposer.RegisterCollectable(registry);

    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(200));
        norm_dist.Observe(ud(e));
    }

    return 0;
}