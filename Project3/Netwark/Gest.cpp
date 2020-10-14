#include<DxLib.h>
#include "Gest.h"

Gest::Gest()
{
	_active = false;
}

Gest::~Gest()
{
}

NetworkMode Gest::GetMode(void)
{
	return NetworkMode(NetworkMode::GEST);
}

bool Gest::ConnectHost(IPDATA hostip)
{
	_nethandle = ConnectNetWork(hostip);
	return _active;
}