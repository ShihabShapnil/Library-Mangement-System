#include <ctime>
#include <chrono>
#include <cstddef>

using namespace std;

class Datecounter {
public:
	Datecounter();
	size_t getDate() const;
	//this will allow us to check the time

private:
	chrono::time_point<chrono::high_resolution_clock> time;
	//the time_point will be allocated to the time now 
	//this will allow us to see the time that the counter was created
	size_t secs_per_day = 5;
};

