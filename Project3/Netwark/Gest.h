#pragma once
#include "NetWorkst.h"
class Gest :
	public NetWorkst
{
public:
	Gest();
	~Gest();
private:

	long long _lcnt = 0;

	NetworkMode GetMode(void)override;

	ActivState ConnectHost(IPDATA hostip)override;
};

