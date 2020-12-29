#include<DxLib.h>
#include "NetWorkst.h"
#include <functional>

NetWorkst::NetWorkst()
{
	// = std::bind(ActivState::Wait, this);
	// = std::bind(ActivState::Init, this);
	// = std::bind(ActivState::Stanby, this);
	// = std::bind(ActivState::Play, this);
	// = std::bind(ActivState::OffLine, this);

	_Pdata.handle = 0;
	_Pdata.playerID = 0;
	_Pdata.state = 0;

	_act = ActivState::Non;
	_active = false;
}

NetWorkst::~NetWorkst()
{
}

void NetWorkst::SetHandle(void)
{
	_Pdata.handle = _nethandle;
}

void NetWorkst::SetPlayerID(void)
{
}

void NetWorkst::SetState(void)
{
	_Pdata.state = static_cast<int>(_act);
}

int NetWorkst::GetHandle(void)
{
	return _nethandle;
}

int NetWorkst::GetPlayerID(void)
{
	return _Pdata.playerID;
}

bool NetWorkst::GetActive(void)
{
	return _active;
}

ActivState NetWorkst::GetActivest(void)
{
	if(GetMode() == NetworkMode::OFF)
	{
		_act = ActivState::OffLine;
	}
	return _act;
}

ActivState NetWorkst::ConnectHost(IPDATA hostip)
{
	return _act;
}

bool NetWorkst::CheckNetwork(void)
{
	return false;
}

bool NetWorkst::CheckLostNetwork(void)
{
	return false;
}

