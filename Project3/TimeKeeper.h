#include<chrono>
#pragma once

#define lpTime TimeKeeper::GetInstance()

class TimeKeeper
{
public:
	static TimeKeeper& GetInstance(void)
	{
		if (t_Instance == nullptr)
		{
			t_Instance = new TimeKeeper();
		}
		return *t_Instance;
	}
	~TimeKeeper();

	std::chrono::system_clock::time_point GetTime(void);
	long long  SystemTimemilli(std::chrono::system_clock::time_point _start, std::chrono::system_clock::time_point _end);
	long long  SystemTimeseconds(std::chrono::system_clock::time_point _start, std::chrono::system_clock::time_point _end);
	long long  SystemTimemicro(std::chrono::system_clock::time_point _start, std::chrono::system_clock::time_point _end);
private:

	TimeKeeper();
	static TimeKeeper* t_Instance;
};

