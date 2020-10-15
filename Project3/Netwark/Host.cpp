#include<DxLib.h>
#include "Host.h"

Host::Host()
{
	_active = !PreparationListenNetWork(_portnum);
}

Host::~Host()
{
}

NetworkMode Host::GetMode(void)
{
	return NetworkMode(NetworkMode::HOST);
}

bool Host::CheckNetwork(void)
{
	while (!ProcessMessage())
	{
		_nethandle = GetNewAcceptNetWork();
		if (_nethandle != -1)
		{
			break;
		}
	}

	return false;
}
