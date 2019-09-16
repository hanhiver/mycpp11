#include <iostream>
#include <chrono>

template <typename V, typename R>
std::ostream& operator << (std::ostream& s, const std::chrono::duration<V,R>& d)
{
	s << "[" << d.count() << " of " << R::num << "/" << R::den << " s]";
	return s;
}

int main()
{
	std::chrono::seconds twentySecond(20);
	std::chrono::hours aDay(24);
	std::chrono::milliseconds ms; 

	ms += twentySecond + aDay;
	-- ms;
	ms *= 2;

	std::cout << ms.count() << " ms" << std::endl;
	std::cout << std::chrono::nanoseconds(ms).count() << " ns" << std::endl;

	std::chrono::milliseconds d(42);
	std::cout << d << std::endl;
}