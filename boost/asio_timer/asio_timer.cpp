#include <iostream>
#include <boost/asio.hpp>

boost::asio::io_service io_service;
boost::posix_time::seconds interval(1); // 1 second
boost::asio::deadline_timer timer(io_service, interval);

void tick(const boost::system::error_code& /*e*/)
{
    std::cout << "tick" << std::endl;

    // Reschedule the timer for 1 second in the future:
    timer.expires_at(timer.expires_at() + interval);
    // Posts the timer event
    timer.async_wait(tick);
}

int main(void)
{
    // Schedule the timer for the first time:
    timer.async_wait(tick);
    // Enter IO loop. The timer will fire for the first time 1 second from now:
    io_service.run();
    return 0;
}