#include<DxLib.h>
#include "NetWorkst.h"
#include <functional>

NetWorkst::NetWorkst()
{
	// = std::bind(ActivState::Wait, this);
	//= std::bind(ActivState::Init, this);
	//= std::bind(ActivState::Stanby, this);
	//= std::bind(ActivState::Play, this);
	//= std::bind(ActivState::OffLine, this);

	_act = ActivState::Non;
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
