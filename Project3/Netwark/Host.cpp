#include<DxLib.h>
#include"Network.h"
#include "Host.h"

Host::Host()
{
	_lcnt = LoginCnt;
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
	MesPacket _mpack;

	

	_act = ActivState::Wait;
	while (!ProcessMessage())
	{
		_nethandle = GetNewAcceptNetWork();
		_Pdata.handle = _nethandle;

		if (_nethandle != -1)
		{
			lpNetwark.SendMes(MesType::COUNT_ROOM);
			//if ()
			//{
				continue;
			//}
			StopListenNetWork();
			_act = ActivState::Init;
			break;
		}
	}
	return false;
}

bool Host::CheckLostNetwork(void)
{
	_losthandle = GetLostNetWork();

	if (_losthandle == _nethandle)
	{
		_nethandle = 0;
		_active = !PreparationListenNetWork(_portnum);
		_act = ActivState::Wait;
		return true;
	}
	return false;
}
