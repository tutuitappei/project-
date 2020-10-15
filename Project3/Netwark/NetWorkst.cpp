#include<DxLib.h>
#include "NetWorkst.h"

NetWorkst::NetWorkst()
{
	_active = false;
}

NetWorkst::~NetWorkst()
{
}

int NetWorkst::GetHandle(void)
{
	return _nethandle;
}

bool NetWorkst::GetActive(void)
{
	return _active;
}

bool NetWorkst::ConnectHost(IPDATA hostip)
{
	return false;
}

bool NetWorkst::CheckNetwork(void)
{
	return false;
}
