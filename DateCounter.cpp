#include "Datecounter.h"
#include <ctime>
#include <chrono>
#include <cstddef>

using namespace std;

Datecounter Date_Counter;

Datecounter::Datecounter()
	:time(std::chrono::high_resolution_clock::now()) {}

std::size_t Datecounter::getDate() const
{
	auto t_diff = std::chrono::high_resolution_clock::now() - time;
	//This'll give us the difference in time from before.
	return std::chrono::duration<double>(t_diff).count() / secs_per_day;
	//this will take the 5 seconds per day and be divided from the total allocated time.
}

