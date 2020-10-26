#include<DxLib.h>
#include<iostream>
#include <fstream>
#include<string>
#include "Network.h"
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
		TRACE("SetNetWorkModeで異常発生");
		break;
	}
	return false;
}

NetworkMode Netwark::GetNetWorkMode(void)
{
	return _state->GetMode();
}

int Netwark::GetNetHandle(void)
{
	return _state->GetHandle();
}

bool Netwark::GetActive(void)
{
	return _state->GetActive();
}

void Netwark::GetRevStanby(void)
{
	MesData _mesd;
	_mesd.type = MesType::NON;
	while (_mesd.type != MesType::STANBY)
	{
		NetWorkRecv(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
	}
}

void Netwark::GetRevStart(void)
{
	MesData _mesd;
	_mesd.type = MesType::STANBY;
	while (_mesd.type != MesType::GAME_S)
	{
		NetWorkRecv(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
	}
	TRACE("ゲーム開始合図の受信\n");
}

void Netwark::SendStanby(void)
{
	MesData _mesd;
	_mesd.data[0] = 0;
	_mesd.data[1] = 0;
	_mesd.type = MesType::STANBY;
	NetWorkSend(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
}

void Netwark::SendStart(void)
{
	MesData _mesd;
	_mesd.data[0] = 0;
	_mesd.data[1] = 0;
	_mesd.type = MesType::GAME_S;
	NetWorkSend(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
}

ActivState Netwark::GetActiveST(void)
{
	return _state->GetActivest();
}

ActivState Netwark::ConnectHost(IPDATA hostip)
{
	return _state->ConnectHost(hostip);
}

bool Netwark::ChecLink(void)
{
	return _state->CheckNetwork();
}

bool Netwark::CheckLost(void)
{
	return _state->CheckLostNetwork();
}

void Netwark::Oneletter(void)
{
	MesData _mesd;
	_mesd.type = MesType::TMX_DATA;
	_mesd.data[0] = 0;
	_mesd.data[1]= 0;
	std::ifstream fs("map/untitled2.tmx");
	char _mapbox;
	while (fs.get(_mapbox))
	{
		_mesd.data[1] = static_cast<int>(_mapbox);
		NetWorkSend(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
		_mesd.data[0]++;
		TRACE("送った文字数は%d\n", _mesd.data[0]);
	}
}

void Netwark::TmxChat(void)
{
	MesData _mesd;
	_mesd.type = MesType::STANBY;
	_mesd.data[0] = 0;
	_mesd.data[1] = 0;
	while (_mesd.type != MesType::TMX_SIZE)
	{
		if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(_mesd))
		{
			NetWorkRecv(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
			_box.resize(_mesd.data[0]);
			TRACE("受け取ったサイズは%d\n", _mesd.data[0]);
		}
	}

}

void Netwark::TmxCheck(const char* filename)
{
	MesData _mesd;


	std::ifstream fs(filename);
	fs.seekg(0, std::ios_base::end);
	_mesd.type = MesType::TMX_SIZE;
	_mesd.data[0] = fs.tellg();
	TRACE("%d\n", _mesd.data[0]);
	NetWorkSend(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
}

void Netwark::TmxDataSend(void)
{

}

void Netwark::TmxDataRev(void)
{
	MesData _mesd;
	_mesd.type = MesType::TMX_SIZE;
	_mesd.data[0] = 0;
	while (_mesd.type != MesType::TMX_DATA)
	{
		NetWorkRecv(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
		(static_cast<char>(_mesd.data[1]));
		TRACE("%d\n", );
	}
}

Netwark::Netwark()
{
}

Netwark::~Netwark()
{
}
