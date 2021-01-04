#include "TimeKeeper.h"

TimeKeeper* TimeKeeper::t_Instance = nullptr;

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

long long TimeKeeper::SystemTimemilli(std::chrono::system_clock::time_point _start, std::chrono::system_clock::time_point _end)
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
}

long long TimeKeeper::SystemTimeseconds(std::chrono::system_clock::time_point _start, std::chrono::system_clock::time_point _end)
{
	return std::chrono::duration_cast<std::chrono::seconds>(_end - _start).count();
}

long long TimeKeeper::SystemTimemicro(std::chrono::system_clock::time_point _start, std::chrono::system_clock::time_point _end)
{
	return std::chrono::duration_cast<std::chrono::microseconds>(_end - _start).count();
}
