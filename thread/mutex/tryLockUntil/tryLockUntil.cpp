#include <iostream>
#include <chrono>
#include <mutex>
#include <ctime>
#include <thread>

std::timed_mutex cinderella;

// Get the time_point of midnight. 
std::chrono::time_point<std::chrono::system_clock> midnight()
{
	using std::chrono::system_clock;
	std::time_t tt = system_clock::to_time_t(system_clock::now());
	struct std::tm* ptm = std::localtime(&tt);
	++ ptm->tm_mday;
	ptm->tm_hour = 0;
	ptm->tm_min = 0;
	ptm->tm_sec = 0;

	return system_clock::from_time_t(mktime(ptm));
}

void carriage()
{
	if (cinderella.try_lock_until(midnight()))
	{
		std::cout << "ride back home on carriage." << std::endl;
	}
	else
	{
		std::cout << "carriage reverts to pumpkin. " << std::endl;
	}
}

void ball() 
{
	cinderella.lock();
	std::cout << "at the ball... " << std::endl;
	cinderella.unlock();
}

int main()
{
	std::thread th1(ball);
	std::thread th2(carriage);
	th1.join();
	th2.join();

	return 0;
}