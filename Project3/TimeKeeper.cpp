#include "TimeKeeper.h"

TimeKeeper::TimeKeeper()
{
}

TimeKeeper::~TimeKeeper()
{
}

std::chrono::system_clock::time_point TimeKeeper::GetTime(void)
{
	return std::chrono::system_clock::now();
}

long long TimeKeeper::SystemTime(std::chrono::system_clock::time_point _start, std::chrono::system_clock::time_point _end)
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
}
