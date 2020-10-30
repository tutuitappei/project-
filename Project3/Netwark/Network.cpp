#include<DxLib.h>
#include<iostream>
#include <fstream>
#include<string>
#include <vector>
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
		TRACE("SetNetWorkMode�ňُ픭��");
		break;
	}
	return false;
}

void Netwark::Updata(void)
{
}

void Netwark::Thread(void)
{

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
	_mesd.type = MesType::TMX_DATA;
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
	TRACE("�Q�[���J�n���}�̎�M\n");
}

void Netwark::SendStanby(void)
{
	MesData _mesd;
	_mesd.data[0] = 0;
	_mesd.data[1] = 0;
	_mesd.type = MesType::STANBY;
	NetWorkSend(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
	TRACE("�J�n�҂���Ԃ̑��M\n");
}

void Netwark::SendStart(void)
{
	MesData _mesd;
	_mesd.data[0] = 0;
	_mesd.data[1] = 0;
	_mesd.type = MesType::GAME_S;
	NetWorkSend(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
	TRACE("�Q�[���J�n���}�̑��M\n");
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

void Netwark::TmxChat(void)
{
	MesData _mesd;
	_mesd.type = MesType::STANBY;
	_mesd.shortd = 0;
	_mesd.chard = 0;
	_mesd.data[0] = 0;
	_mesd.data[1] = 0;
	
	while (_mesd.type != MesType::TMX_SIZE)
	{
		if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(_mesd))
		{
			NetWorkRecv(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
			_box.resize(_mesd.data[0]);
			TRACE("�󂯎�����T�C�Y��%d\n", _mesd.data[0]);
		}
		bot = _mesd.data[0];
	}

}

void Netwark::TmxCheck(const char* filename)
{
	MesData _mesd;


	std::ifstream fs(filename);
	fs.seekg(0, std::ios_base::end);
	_mesd.type = MesType::TMX_SIZE;
	_mesd.shortd = 0;
	_mesd.chard = 0;
	_mesd.data[0] = fs.tellg();
	_mesd.data[1] = 0;
	TRACE("%d\n", _mesd.data[0]);
	NetWorkSend(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
}

void Netwark::TmxDataSend(void)
{

}

void Netwark::TmxDataRev(void)
{
	//std::ofstream ifs("test.tmx");
	//if (!ifs) {
	//	TRACE("�t�@�C���I�[�v���Ɏ��s\n");
	//}


	//MesData _mesd;
	//_mesd.type = MesType::TMX_SIZE;
	//_mesd.data[0] = 0;
	//int _numdata;
	//char _numbox;
	//while ((_mesd.type != MesType::TMX_DATA)||(_mesd.shortd != bot))
	//{
	//	NetWorkRecv(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
	//	_numdata = _mesd.data[1];
	//	_numbox = static_cast<char>(_numdata);
	//	_box = static_cast<TmxBox>(_numbox);
	//	TRACE("ID%d  Data%d\n",_mesd.shortd);
	//}

	start = std::chrono::system_clock::now();
	LetterReceive();
	end = std::chrono::system_clock::now();
	TRACE("%d�~���b\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

void Netwark::Oneletter(void)
{
	//MesData _mesd;
	//_mesd.type = MesType::TMX_DATA;
	//_mesd.data[0] = 0;
	//_mesd.data[1] = 0;
	//std::ifstream ifs("map/untitled2.tmx");
	//char _mapbox;
	//while (ifs.get(_mapbox))
	//{
	//	_mesd.data[1] = static_cast<int>(_mapbox);
	//	NetWorkSend(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
	//	_mesd.data[0]++;
	//	TRACE("��������������%d\n", _mesd.data[0]);
	//}

	start = std::chrono::system_clock::now();
	LetterSet();
	end = std::chrono::system_clock::now();
	TRACE("%d�~���b\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

void Netwark::LetterReceive(void)
{
	MesData _mesd;
	unionData _uniond;
	_mesd.type = MesType::TMX_DATA;
	_mesd.data[0] = 0;
	_mesd.data[1] = 0;
	std::string fs;

	std::ofstream ofs("map/revmap.tmx");
	std::ifstream ifs("tmx.dat");
	if ((!ofs)||(!ifs))
	{		
		TRACE("�t�@�C���I�[�v���Ɏ��s\n");
	}

	if (!ofs.eof())
	{
		do
		{
			if (ofs.eof())
			{
				break;
			}
		} while (fs.find("data encoding ") == std::string::npos);
		_uniond.iData[0] = _mesd.data[0];
		_uniond.iData[1] = _mesd.data[1];
	}
	
}

void Netwark::LetterSet(void)
{
	MesData _mesd;
	unionData _uniond;
	_mesd.type = MesType::TMX_DATA;
	_mesd.data[0] = 0;
	_mesd.data[1] = 0;
	std::ifstream ifs("map/untitled2.tmx");
	std::string fs;
	//std::iostream 

	//auto GetLetters = [&]() {
	//};

	while (!ifs.eof())
	{
		do
		{
			if (ifs.eof())
			{
				break;
			}
		} while (fs.find("data encoding ") == std::string::npos);
		if (!ifs.eof())
		{
			//ifs.getline();
			while (fs.find("< / data>") == std::string::npos)
			{
			}
		}

	}
	if (SendWait())
	{

	}
}

bool Netwark::SendWait(void)
{
	//if ()
	//{
	//	return true;
	//}
	return false;
}
Netwark::Netwark()
{
}

Netwark::~Netwark()
{
}

