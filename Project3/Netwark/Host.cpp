#include<DxLib.h>
#include "Host.h"

Host::Host()
{
	_active = !PreparationListenNetWork(_portnum);
	_act = ActivState::Non;
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

	_act = ActivState::Wait;
	while (!ProcessMessage())
	{
		_nethandle = GetNewAcceptNetWork();
		if (_nethandle != -1)
		{

			StopListenNetWork();
			_act = ActivState::Init;
			break;
		}
	}
	return false;
}
