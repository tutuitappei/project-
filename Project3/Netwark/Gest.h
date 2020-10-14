#pragma once
#include "NetWorkst.h"
class Gest :
	public NetWorkst
{
public:
	Gest();
	~Gest();
private:
	NetworkMode GetMode(void)override;

	bool ConnectHost(IPDATA hostip)override;
};

