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
    using Family_Counter = prometheus::Family<prometheus::Counter>&;

    // create an http server running on port 5001. 
    //Exposer exposer {"0.0.0.0:5001"};
    Exposer* exposer_ptr = new Exposer {"0.0.0.0:5001"};

    // create a metrics registry with component=main labels applied to all its metrics. 
    auto registry = std::make_shared<Registry>();

    std::pair<std::string, std::string> my_label1 = std::make_pair("label1", "DHAN");
    std::pair<std::string, std::string> my_label2 = std::make_pair("label2", "HWC");

    // add a new counter family to the registry. 
    // families combine values with the same name, 
    // but distinct label dimensions. 
    //auto& counter_family = 
    Family_Counter counter_family =
        BuildCounter()
        .Name("time_runing_seconds_total")
        .Help("How many seconds is this server running? ")
        .Labels({})
        .Register(*registry);

    // add a counter to the metric family
    auto& time_counter = counter_family.Add({my_label1, my_label2});
        //{{"another_label", "value"}, {"yet_another_label", "value"}});

    auto& restart_counter = counter_family.Add(
        {{"content", "restart"}, {"index", "times"}});

    // ask the exposer to scrape the registry on incoming scrapes. 
    //exposer.RegisterCollectable(registry);
    exposer_ptr->RegisterCollectable(registry);

    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // increment the counter by one (second)
        time_counter.Increment();
        //restart_counter.Increment(3);
    }
    return 0;
}

