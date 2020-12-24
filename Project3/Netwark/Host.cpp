#include<DxLib.h>
#include"../_debug/_DebugConOut.h"
#include"Network.h"
#include "Host.h"

Host::Host()
{
	_lcnt = LoginCnt;
	cntstart = false;
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
	unionData _hosuni;

	_mpack.clear();
	_hosuni.uiData = 0;
	for (int i = 0; i < 4; i++)
	{
		_hosuni.cData[i] = 0;
	}
	_hosuni.iData = 0;

	_act = ActivState::Wait;
	//while (!ProcessMessage())
	{
		_nethandle = GetNewAcceptNetWork();
		_Pdata.handle = _nethandle;

		if (_nethandle != -1)
		{
			if (!cntstart)
			{
				start = std::chrono::system_clock::now();
				cntstart = true;
			}
			point = std::chrono::system_clock::now();
			
			lpNetwark.SendMes(MesType::COUNT_ROOM,_mpack);
			//if (_lcnt > std::chrono::duration_cast<std::chrono::milliseconds>(point - start).count())
			//{
				//continue;
			//}
			StopListenNetWork();
			_act = ActivState::Init;
			//break;
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
