#include<DxLib.h>
#include"Network.h"
#include "Gest.h"

Gest::Gest()
{
	_act = ActivState::Non;
}

Gest::~Gest()
{
}

NetworkMode Gest::GetMode(void)
{
	return NetworkMode(NetworkMode::GEST);
}

ActivState Gest::ConnectHost(IPDATA hostip)
{
	_nethandle = ConnectNetWork(hostip, _portnum);
	_Pdata.handle = _nethandle;
	if (_nethandle >= 0)
	{
		//while ()
		//{

		//}
		_act = ActivState::Init;

	}


	return _act;
}