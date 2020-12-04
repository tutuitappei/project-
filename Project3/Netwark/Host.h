#pragma once
#include<chrono>
#include "NetWorkst.h"

#define LoginCnt 15000;

class Host :
	public NetWorkst
{
public:
	Host();
	~Host();
private:
	long long _lcnt = 0;
	bool cntstart;

	std::chrono::system_clock::time_point  start, point;

	NetworkMode GetMode(void) override;
	bool CheckNetwork(void) override;
	bool CheckLostNetwork(void) override;
};

