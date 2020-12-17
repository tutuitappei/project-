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
		TRACE("SetNetWorkModeで異常発生");
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

bool Netwark::SendMes(MesType _mtype)
{
	MesPacket data;
	SendMes(_mtype, std::move(data));
	return false;
}

bool Netwark::SendMes(MesType _mtype, MesPacket _mpacket)
{
	int _intSendCnt = 1400;

	MesData data;
	data.sendID = 0;
	Header header(Header{ _mtype,0,0,0 });

	_mpacket.insert(_mpacket.begin(), { header.hamu[1] });
	_mpacket.insert(_mpacket.begin(), { header.hamu[0] });

	auto _headerSize = sizeof header;

	do
	{
		if (_mpacket.size() < _intSendCnt)
		{

			header.hd.length = _mpacket.size() - 2;
			header.hd.next = 0;
			NetWorkSend(GetNetHandle(), &_mpacket, sizeof(_mpacket));
			_mpacket.erase(_mpacket.begin() + _headerSize, _mpacket.end());
		}
		else if (_mpacket.size() >= _intSendCnt)
		{
			header.hd.length = _intSendCnt - 2;
			header.hd.next = 1;


			NetWorkSend(GetNetHandle(), &_mpacket, sizeof(_intSendCnt));
			_mpacket.erase(_mpacket.begin() + _headerSize, _mpacket.begin() + _intSendCnt);
		}
		else
		{
			TRACE("_mpacket.sizeもしくは_intSendCntが異常です\n");
		}
		data.sendID++;
	} while (header.hd.next != 0);

	return false;
}

bool Netwark::IrregularCheck(MesType _mestype)
{

	return false;
}

void Netwark::FuncMode(MesType _mestype)
{

}

void Netwark::RecvMes(void)
{
	_funcmode = [&](MesType _mestype) {
		switch (_mestype)
		{
		case MesType::COUNT_ROOM:
			break;
		case MesType::ID:
			break;
		case MesType::TMX_SIZE:
			break;
		case MesType::TMX_DATA:
			break;
		case MesType::STANBY_HOST:
			break;
		case MesType::STANBY_GEST:
			break;
		case MesType::COUNT_GAME:
			break;
		case MesType::POS:
			break;
		case MesType::BOM_SET:
			break;
		case MesType::DETH:
			break;
		case MesType::LOST:
			break;
		default:
			TRACE("不明なデータの受信\n");
			break;
		}
	};
	//int _intSendCnt = 1400;

	//MesData data;
	//data.sendID = 0;
	//Header header;

	//_mpacket.insert(_mpacket.begin(), { header.hamu[1] });
	//_mpacket.insert(_mpacket.begin(), { header.hamu[0] });

	//auto _headerSize = sizeof header;

	RevPacket _mpacket;
	MesType _mtype{ MesType::NON };
	Header header(Header{ _mtype,0,0,0 });
	auto _headerSize = sizeof header;

	NetWorkRecv(GetNetHandle(), &_mpacket, sizeof(_mpacket));
	_mpacket;
	if (IrregularCheck(_mpacket.first))
	{
		TRACE("イレギュラーの発生\n");
	}
	else
	{
		list.push_back((header.hd.type, _mpacket));
		_funcmode(_mpacket.first);
	}
	

	//do
	//{
	//	if (_mpacket.size() < _intSendCnt)
	//	{
	//		//header.hd.lenght = _mpacket.size() - 2;
	//		header.hd.next = 0;

	//		NetWorkSend(GetNetHandle(), &_mpacket, sizeof(_mpacket));
	//		_mpacket.erase(_mpacket.begin() + _headerSize, _mpacket.end());
	//	}
	//	else if (_mpacket.size() >= _intSendCnt)
	//	{
	//		//header.hd.lenght = _intSendCnt - 2;
	//		header.hd.next = 1;


	//		NetWorkSend(GetNetHandle(), &_mpacket, sizeof(_intSendCnt));
	//		_mpacket.erase(_mpacket.begin() + _headerSize, _mpacket.begin() + _intSendCnt);
	//	}
	//	else
	//	{
	//		TRACE("_mpacket.sizeもしくは_intSendCntが異常です\n");
	//	}
	//	data.sendID++;
	//} while (header.hd.next != 0);

}

void Netwark::GetRevStanby(void)
{
	MesData _mesd;
	_mesd.type = MesType::TMX_DATA;
	while (_mesd.type != MesType::STANBY_HOST)
	{
		NetWorkRecv(GetNetHandle(), &_mesd, sizeof(_mesd));
	}
	TRACE("初期化情報の受信\n");
}

void Netwark::GetRevStart(void)
{
	MesData _mesd;
	_mesd.type = MesType::STANBY_HOST;
	while (_mesd.type != MesType::STANBY_GEST)
	{
		NetWorkRecv(lpNetwark.GetNetHandle(), &_mesd, sizeof(_mesd));
	}
	TRACE("ゲーム開始合図の受信\n");
}

void Netwark::SendStanby(void)
{
	MesData _mesd;
	_mesd.type = MesType::STANBY_HOST;
	NetWorkSend(GetNetHandle(), &_mesd, sizeof(_mesd));
	SendMes(MesType::STANBY_HOST);
	TRACE("開始待ち状態の送信\n");
}

void Netwark::SendStart(void)
{
	MesData _mesd;
	_mesd.type = MesType::STANBY_GEST;
	NetWorkSend(GetNetHandle(), &_mesd, sizeof(_mesd));
	SendMes(MesType::STANBY_GEST);
	TRACE("ゲーム開始合図の送信\n");
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
	//MesData _mesd;
	//_mesd.type = MesType::STANBY_HOST;
	//_mesd.sendID = 0;
	//_mesd.next = 0;
	//_mesd.data[0] = 0;
	//_mesd.data[1] = 0;
	//
	//while (_mesd.type != MesType::TMX_SIZE)
	//{
	//	if (GetNetWorkDataLength(GetNetHandle()) >= sizeof(_mesd))
	//	{
	//		NetWorkRecv(GetNetHandle(), &_mesd, sizeof(_mesd));
	//		_box.resize(_mesd.data[0]);
	//		TRACE("受信したサイズは%d\n", _mesd.data[0]);
	//	}
	//	bot = _mesd.data[0];
	//}

}

void Netwark::TmxCheck(const char* filename)
{
	MesData _mesd;
	unionData _data;
	MesPacket packet;

	_data.cData[0] = 21;
	_data.cData[1] = 17;
	_data.cData[2] = 4;
	_data.cData[3] = 0;

	std::ifstream fs(filename);
	fs.seekg(0, std::ios_base::end);
	_mesd.type = MesType::TMX_SIZE;
	_mesd.sendID = 0;
	_mesd.next = 0;

	auto size = fs.tellg();
	
	TRACE("受け取ったサイズは%dです\n", static_cast<int>(size));

	//SendMes(_mesd.type, );

	NetWorkSend(GetNetHandle(), &_mesd, sizeof(_mesd));
}

void Netwark::TmxDataSend(void)
{

}

void Netwark::TmxDataRev(void)
{
	std::ofstream ifs("test.tmx");
	if (!ifs) {
		TRACE("ファイルオープンに失敗\n");
	}


	start = std::chrono::system_clock::now();
	MesData _mesd;
	_mesd.type = MesType::TMX_SIZE;
	//_mesd.data[0] = 0;
	int _numdata;
	char _numbox;
	while ((_mesd.type != MesType::TMX_DATA))
	{
		NetWorkRecv(GetNetHandle(), &_mesd, sizeof(_mesd));
		_numdata = _mesd.length;
		_numbox = static_cast<char>(_numdata);
		_box = static_cast<TmxBox>(_numbox);
		//TRACE("ID%d  Data%d\n",_mesd.data[0],_numdata);
	}

	//LetterReceive();
	end = std::chrono::system_clock::now();
	//TRACE("%dミリ秒\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

void Netwark::Oneletter(void)
{
	start = std::chrono::system_clock::now();
	MesData _mesd;
	_mesd.type = MesType::TMX_DATA;
	//_mesd.data[0] = 0;
	//_mesd.data[1] = 0;
	std::ifstream ifs("map/untitled2.tmx");
	char _mapbox;

	while (ifs.get(_mapbox))
	{
		//_mesd.data[1] = static_cast<int>(_mapbox);
		NetWorkSend(GetNetHandle(), &_mesd, sizeof(_mesd));
		//_mesd.data[0]++;
	}

	//LetterSet();
	end = std::chrono::system_clock::now();
	//TRACE("%dミリ秒\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

void Netwark::LetterReceive(void)
{
	MesData _mesd;
	unionData _uniond;
	_mesd.type = MesType::TMX_DATA;

	std::string fs;

	std::ofstream ofs("map/revmap.tmx");
	std::ifstream ifs("tmx.dat");
	if ((!ofs)||(!ifs))
	{		
		TRACE("何かのファイルオープンに失敗\n");
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
		//_uniond.iData[0];
	}
	
}

void Netwark::LetterSet(void)
{
	MesPacket _data;
	SetHeader(Header{ MesType::TMX_SIZE,0,0,1 }, _data);


	NetWorkSend(GetNetHandle(), &_data, sizeof(_data));


	MesData _mesd;
	_mesd.type = MesType::TMX_DATA;
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

void Netwark::SetHeader(Header head, MesPacket pack)
{


}

void Netwark::SendHeader(void)
{
}


void Netwark::SetPlayerNum(int id)
{
	playerID = id;
	maxplayer++;
}

int Netwark::GetPlayerID(void)
{
	return _state->GetPlayerID();
}

int Netwark::GetPlayerMAX(void)
{
	return maxplayer;
}

Netwark::Netwark()
{
}

Netwark::~Netwark()
{
}

