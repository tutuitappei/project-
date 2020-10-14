#pragma once
#include "NetWorkst.h"
class Host :
	public NetWorkst
{
public:
	Host();
	~Host();
private:
	NetworkMode GetMode(void) override;
};

