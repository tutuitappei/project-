#pragma once
#include "NetWorkst.h"

#define LoginCnt 1500;

class Host :
	public NetWorkst
{
public:
	Host();
	~Host();
private:

	long long _lcnt = 0;

	NetworkMode GetMode(void) override;
	bool CheckNetwork(void) override;
	bool CheckLostNetwork(void) override;
};

