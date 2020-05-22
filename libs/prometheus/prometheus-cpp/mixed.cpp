#include <chrono>
#include <map> 
#include <memory> 
#include <string> 
#include <thread> 
#include <random> 

#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <prometheus/counter.h>
#include <prometheus/gauge.h>
#include <prometheus/histogram.h>

int main(int argc, char* argv[])
{
    using namespace prometheus;
    using BucketBoundaries = std::vector<double>;

    // Create a server in port 5001.
    Exposer expose {"0.0.0.0:5001"};

    std::knuth_b e; 
    std::uniform_real_distribution<double> ud(0.0, 10.0);

    BucketBoundaries bb {2.0, 4.0, 6.0, 8.0};

    // Create a metrics registry. 
    auto registry = std::make_shared<Registry>();

    // 需要分成不同model分别对应的，还要区分resful和grpc不同的量。
    auto& edi_service_served_clients = 
            BuildCounter()
                .Name("edi_service_served_clients")
                .Help("Total  Inference requests to an EDI severed model")
                .Labels({{"apps", "EDI"}})
                .Register(*registry);

    // isd
    auto& edi_service_pending_requests = 
            BuildGauge()
                .Name("edi_service_pending_requests")
                .Help("Total Pending Inference requests")
                .Labels({{"apps", "EDI"}})
                .Register(*registry);

    auto& edi_service_request_per_sec = 
            BuildGauge()
                .Name("edi_service_request_per_sec")
                .Help("current requests per second")
                .Labels({{"apps", "EDI"}})
                .Register(*registry);

    auto& edi_service_data_size_per_sec = 
            BuildGauge()
                .Name("edi_service_data_size_per_sec")
                .Help("current payload data size per second")
                .Labels({{"apps", "EDI"}})
                .Register(*registry);

    auto& edi_service_running_kernels = 
            BuildGauge()
                .Name("edi_service_running_kernels")
                .Help("current running kernel number")
                .Labels({{"apps", "EDI"}})
                .Register(*registry);

}