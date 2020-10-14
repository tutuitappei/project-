#include<DxLib.h>
#include "Netwark.h"
#include"../_debug/_DebugConOut.h"
#include"Host.h"
#include"Gest.h"

Netwark* Netwark::s_Instance = nullptr;

IPDATA Netwark::GetIp()
{
	IPDATA ip;
	GetMyIPAddress(&ip);
	return ip;
}

bool Netwark::SetNetWorkMode(NetworkMode mode)
{
	switch (mode)
	{
	case NetworkMode::OFF:
		_state = std::make_unique<NetWorkst>();
		break;
	case NetworkMode::HOST:
		_state = std::make_unique<Host>();
		break;
	case NetworkMode::GEST:
		_state = std::make_unique<Gest>();
		break;
	default:
		TRACE("SetNetWorkMode‚ÅˆÙí”­¶");
		break;
	}
	return false;
}

NetworkMode Netwark::GetNetWorkMode(void)
{
	return _state->GetMode();
}

bool Netwark::GetActive(void)
{
	return _state->GetActive();
}

bool Netwark::ConnectHost(IPDATA hostip)
{
	return false;
}

Netwark::Netwark()
{
}

Netwark::~Netwark()
{
}
