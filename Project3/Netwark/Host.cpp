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
