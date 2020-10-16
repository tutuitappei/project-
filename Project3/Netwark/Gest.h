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

	ActivState ConnectHost(IPDATA hostip)override;
};

