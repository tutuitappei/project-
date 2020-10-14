#include<DxLib.h>
#include "NetWorkst.h"

NetWorkst::NetWorkst()
{
	_active = false;
}

NetWorkst::~NetWorkst()
{
}

bool NetWorkst::GetActive(void)
{
	return _active;
}

bool NetWorkst::ConnectHost(IPDATA hostip)
{
	return false;
}
