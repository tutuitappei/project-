#include<chrono>
#pragma once

class TimeKeeper
{
public:
	TimeKeeper();
	~TimeKeeper();

	std::chrono::system_clock::time_point GetTime(void);
	long long  SystemTime(std::chrono::system_clock::time_point _start, std::chrono::system_clock::time_point _end);
private:
};

