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
	_nethandle = ConnectNetWork(hostip, _portnum);
	if (_nethandle >= 0)
	{
		_active = true;

	}
	else
	{
		_active = false;
	}
	return _active;
}