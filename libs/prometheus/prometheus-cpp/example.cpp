#include <chrono> 
#include <map> 
#include <memory>
#include <string> 
#include <thread> 

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

int main(int argc, char* argv[])
{
    using namespace prometheus;

    // create an http server running on port 5001. 
    Exposer exposer {"0.0.0.0:5001"};

    // create a metrics registry with component=main labels applied to all its metrics. 
    auto registry = std::make_shared<Registry>();

    // add a new counter family to the registry. 
    // families combine values with the same name, 
    // but distinct label dimensions. 
    auto& counter_family = BuildCounter()
                            .Name("time_runing_seconds_total")
                            .Help("How many seconds is this server running? ")
                            .Labels({{"label", "value"}})
                            .Register(*registry);

    // add a counter to the metric family
    auto& time_counter = counter_family.Add(
        {{"another_label", "value"}, {"yet_another_label", "value"}});

    // ask the exposer to scrape the registry on incoming scrapes. 
    exposer.RegisterCollectable(registry);

    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // increment the counter by one (second)
        time_counter.Increment();
    }
    return 0;
}