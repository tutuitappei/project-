#include<DxLib.h>
#include<iostream>
#include <sstream>
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
	RunUpdata(); //スレッド化
}

bool Netwark::GetFrag(void)
{
	return startFlag;
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

	Header header{ _mtype,0,0,0 };

	_mpacket.insert(_mpacket.begin(), { header.hamu[1] });
	_mpacket.insert(_mpacket.begin(), { header.hamu[0] });

	auto _headerSize = sizeof(header);

	do
	{
		if (_mpacket.size() < _intSendCnt)
		{

			header.hd.length = _mpacket.size() - 2;
			header.hd.next = 0;
			header.hd.sendID = 0;
			NetWorkSend(GetNetHandle(), _mpacket.data(), sizeof(_mpacket));
			_mpacket.erase(_mpacket.begin() + 2, _mpacket.end());
		}
		else if (_mpacket.size() >= _intSendCnt)
		{
			header.hd.length = _intSendCnt - 2;
			header.hd.next = 1;


			NetWorkSend(GetNetHandle(), _mpacket.data(), sizeof(_intSendCnt));
			_mpacket.erase(_mpacket.begin() + 2, _mpacket.begin() + _intSendCnt);
		}
		else
		{
			TRACE("_mpacket.sizeもしくは_intSendCntが異常です\n");
		}
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

	
	[&](MesType _mestype) {
		/*switch (_mestype)
		{
		case MesType::COUNT_ROOM:
			TRACE("待ち時間カウントダウン受信\n");
			break;
		case MesType::ID:
			TRACE("ID受信\n");
			break;
		case MesType::TMX_SIZE:
			TRACE("TMXサイズ受信\n");
			break;
		case MesType::TMX_DATA:
			TRACE("TMXデータ受信\n");
			break;
		case MesType::STANBY_HOST:
			TRACE("STANBY_HOST受信\n");
			break;
		case MesType::STANBY_GEST:
			TRACE("STANBY_GEST受信\n");
			break;
		case MesType::COUNT_GAME:
			TRACE("ゲームカウントダウン受信\n");
			break;
		case MesType::POS:
			break;
		case MesType::BOM_SET:
			TRACE("ボム設置\n");
			break;
		case MesType::DETH:
			TRACE("死亡受信\n");
			break;
		case MesType::RESULT:
			TRACE("RESULT受信\n");
			break;
		case MesType::LOST:
			TRACE("切断受信\n");
			break;
		default:
			TRACE("不明なデータの受信\n");
			break;
		}*/
	};
	int _intSendCnt = 1400;

	MesData data;
	data.sendID = 0;

	RevPacket _mpacket;
	MesType _mtype{ MesType::NON };
	Header header{ _mtype,0,0,0 };

	//_mpacket.insert(_mpacket.begin(), { header.hamu[1] });
	//_mpacket.insert(_mpacket.begin(), { header.hamu[0] });

	auto _headerSize = sizeof(header);

	if (IrregularCheck(_mpacket.first))
	{
		TRACE("イレギュラーの発生\n");
	}
	else
	{
		list.push_back((header.hd.type, _mpacket));

	}
	do
	{
		NetWorkRecv(GetNetHandle(), &_mpacket, sizeof(_mpacket));
	} while (header.hd.next != 0);

	do
	{
		//if (_mpacket.size() < _intSendCnt)
		//{
		//	header.hd.lenght = _mpacket.size() - 2;
		//	header.hd.next = 0;

		//	NetWorkSend(GetNetHandle(), &_mpacket, sizeof(_mpacket));
		//	_mpacket.erase(_mpacket.begin() + _headerSize, _mpacket.end());
		//}
		//else if (_mpacket.size() >= _intSendCnt)
		//{
		//	header.hd.lenght = _intSendCnt - 2;
		//	header.hd.next = 1;


		//	NetWorkSend(GetNetHandle(), &_mpacket, sizeof(_intSendCnt));
		//	_mpacket.erase(_mpacket.begin() + _headerSize, _mpacket.begin() + _intSendCnt);
		//}
		//else
		//{
		//	TRACE("_mpacket.sizeもしくは_intSendCntが異常です\n");
		//}
		//data.sendID++;
	} while (header.hd.next != 0);

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
	//MesData _mesd;
	//_mesd.type = MesType::STANBY_HOST;
	//NetWorkSend(GetNetHandle(), &_mesd, sizeof(_mesd));
	SendUpdata(MesType::STANBY_HOST);
	TRACE("開始待ち状態の送信\n");
}

void Netwark::SendStart(void)
{
	//MesData _mesd;
	//_mesd.type = MesType::STANBY_GEST;
	//NetWorkSend(GetNetHandle(), &_mesd, sizeof(_mesd));
	SendUpdata(MesType::STANBY_GEST);
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
	packet.clear();
	_data.cData[0] = 21;
	_data.cData[1] = 17;
	_data.cData[2] = 4;
	_data.cData[3] = 0;

	std::ifstream fs(filename);
	fs.seekg(0, std::ios_base::end);
	_mesd.type = MesType::TMX_SIZE;
	_mesd.sendID = 0;
	_mesd.next = 0;

	packet.push_back(_data);

	auto size = fs.tellg();
	
	TRACE("受け取ったサイズは%dです\n", static_cast<int>(size));
	
	SendUpdata(_mesd.type, packet);

	//NetWorkSend(GetNetHandle(), &_mesd, sizeof(_mesd));
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
	//MesPacket _data;
	//SetHeader(Header{ MesType::TMX_SIZE,0,0,1 }, _data);


	//NetWorkSend(GetNetHandle(), &_data, sizeof(_data));


	//MesData _mesd;
	//_mesd.type = MesType::TMX_DATA;
	//std::ifstream ifs("map/untitled2.tmx");
	//std::string fs;
	////std::iostream 

	////auto GetLetters = [&]() {
	////};

	//while (!ifs.eof())
	//{
	//	do
	//	{
	//		if (ifs.eof())
	//		{
	//			break;
	//		}
	//	} while (fs.find("data encoding ") == std::string::npos);
	//	if (!ifs.eof())
	//	{
	//		//ifs.getline();
	//		while (fs.find("< / data>") == std::string::npos)
	//		{
	//		}
	//	}

	//}
	//if (SendWait())
	//{

	//}
}

bool Netwark::SendWait(void)
{
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
	startFlag = false;

	readtmx("map/untitled2.tmx");


	_width = 0;
	_hight = 0;
	_layernum = 0;

	keytype = MesType::NON;
	MesPacket pack;
	using namespace std::placeholders;
	//_funcmode[MesType::COUNT_ROOM] = std::bind(&Netwark::Countroom, _1, this);
	//_funcmode[MesType::ID]; = std::bind(&Netwark::Iddata, this);
	//_funcmode[MesType::STANBY_HOST]; = std::bind(&Netwark::Countroom, this);
	//_funcmode[MesType::STANBY_GEST]; = std::bind(&Netwark::Iddata, this);
	//_funcmode[MesType::COUNT_GAME]; = std::bind(&Netwark::Countroom, this);
	//_funcmode[MesType::TMX_SIZE]; = std::bind(&Netwark::Iddata, this);
	//_funcmode[MesType::TMX_DATA]; = std::bind(&Netwark::Countroom, this);
	//_funcmode[MesType::POS]; = std::bind(&Netwark::Iddata, this);
	//_funcmode[MesType::BOM_SET]; = std::bind(&Netwark::Iddata, this);
	//_funcmode[MesType::DETH]; = std::bind(&Netwark::Countroom, this);
	//_funcmode[MesType::RESULT]; = std::bind(&Netwark::Iddata, this);
	//_funcmode[MesType::LOST]; = std::bind(&Netwark::Iddata, this);
}

Netwark::~Netwark()
{
}


void Netwark::RevUpdata(void)
{
	_funcmode;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Header header;
		auto handle = GetNetHandle();
		std::lock_guard<std::mutex> lock(_mute);	//ロックガード処理
		int cunt = 0;

		if (GetNetWorkDataLength(handle) >= sizeof(header))
		{
			NetWorkRecv(handle, &header, sizeof(header));	//データの受信

			if (header.hd.length >= 1)
			{
				_revdata[header.hd.type].resize(header.hd.length);
				
				if (GetNetWorkDataLength(handle) >= sizeof(unionData) * header.hd.length)
				{
					NetWorkRecv(handle, &_revdata[header.hd.type][cunt], sizeof(unionData) * header.hd.length);
				}
				cunt = header.hd.length;
				while (header.hd.next)
				{
					if (GetNetWorkDataLength(handle) >= sizeof(header))
					{
						NetWorkRecv(handle, &header, sizeof(header));	//データの受信
						_revdata[header.hd.type].resize(cunt + header.hd.length);
						if (GetNetWorkDataLength(handle) >= sizeof(unionData) * header.hd.length)
						{
							NetWorkRecv(handle, &_revdata[header.hd.type][cunt], sizeof(unionData) * header.hd.length);
						}
						cunt += header.hd.length;
					}
				}
			}
			TRACE("受信size%d\n", _revdata[header.hd.type].size());
			//_funcmode[header.hd.type](_revdata[header.hd.type]);
		}
		
	}

}

void Netwark::RunUpdata(void)
{
	//_thread(&Netwark::RevUpdata, this);

	//_thread.detach();

	std::thread th(&Netwark::RevUpdata, this);

	th.detach();
}

void Netwark::SendUpdata(MesType mtype)
{
	MesPacket data;
	SendUpdata(mtype, std::move(data));
}

void Netwark::SendUpdata(MesType mtype, MesPacket mpacket)
{
	int intSendCnt = 1400;
	int cunt = 0;

	Header header{ mtype,0,0,0 };
	auto handle = GetNetHandle();

	//mpacket.emplace(mpacket.begin(),);
	mpacket.insert(mpacket.begin(), { header.hamu[1] });
	mpacket.insert(mpacket.begin(), { header.hamu[0] });

	auto headerSize = sizeof(header);
	
	header.hd.sendID = 0;

	if (GetNetWorkDataLength(handle) >= headerSize)
	{
		do
		{

			if (mpacket.size() <= intSendCnt)
			{

				header.hd.length = mpacket.size() - 2;
				header.hd.next = 0;

				NetWorkSend(GetNetHandle(), mpacket.data(), sizeof(mpacket));
				mpacket.erase(mpacket.begin() + 2, mpacket.end());
			}
			else
			{
				header.hd.length = intSendCnt - 2;
				header.hd.next = 1;


				NetWorkSend(GetNetHandle(), mpacket.data(), sizeof(intSendCnt));
				mpacket.erase(mpacket.begin() + 2, mpacket.begin() + intSendCnt);

				header.hd.sendID++;
			}
			
		} while (header.hd.next);
	}
	
}

void Netwark::Countroom(const MesPacket& mest)
{
}

void Netwark::Iddata(const MesPacket& mest)
{
}

void Netwark::StanbyHost(const MesPacket& mest)
{
	startFlag = true;
}

void Netwark::StanbyGest(const MesPacket& mest)
{
}

void Netwark::Countgame(const MesPacket& mest)
{
}

void Netwark::TmxSize(const MesPacket& mest)
{
}

void Netwark::TmxData(const MesPacket& mest)
{
	std::string fs;
	std::ofstream ofs("map/revmap.tmx");
	std::ifstream ifs("tmx.dat");
	if ((!ofs) || (!ifs))
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

void Netwark::Posd(const MesPacket& mest)
{
}

void Netwark::Bomset(const MesPacket& mest)
{
}

void Netwark::Deth(const MesPacket& mest)
{
	TRACE("死亡を受信\n");
}

void Netwark::Result(const MesPacket& mest)
{
}

void Netwark::LostNet(const MesPacket& mest)
{
	TRACE("切断を受信\n");
}

void Netwark::readtmx(std::string path)
{
	std::ifstream tempfile(path, std::ios::in | std::ios::binary);
	std::string str;
	std::string numstr;
	std::stringstream strstream;
	std::string s;
	unionData udata;
	MesPacket datapacket;
	unionData sizedata;

	int writecnt = 0;

	while (!tempfile.eof())
	{
		std::getline(tempfile, str);
		if (str.find("layer id") != -1)
		{
			_layernum++;
			sizedata.cData[2] = _layernum;
		}
		if (str.find("map version") != -1)
		{
			strstream.str(str);
			do
			{
				std::getline(strstream, s, '"');
				if (_width == 0)
				{
					if (s.find("width=") != -1)
					{
						std::getline(strstream, s, '"');
						sizedata.cData[0] = std::stoi(s);
						_width = sizedata.cData[0];
						TRACE("W%d\n", _width);
					}
				}
				if (_hight == 0)
				{
					if (s.find("height=") != -1)
					{
						std::getline(strstream, s, '"');
						sizedata.cData[1] = std::stoi(s);
						_hight = sizedata.cData[1];
						TRACE("H%d\n", _hight);
					}
				}

			} while (!strstream.eof());
		}
		if (str.find_first_of("data encoding") == std::string::npos)
		{
			strstream.str(str);
			strstream.seekg(0, std::ios::beg);
			do
			{
				std::string str_num = "";
				std::getline(strstream, str_num, ',');

				if (str_num == "\r")
				{
					continue;
				}
				if (str_num.size())
				{
					auto num = std::atoi(str_num.c_str());
					if (writecnt % 2 == 0)
					{
						udata.cData[(writecnt / 2) % 4] = num;
					}
					else
					{
						udata.cData[(writecnt / 2) % 4] |= ((num << 4) & 0xff);
					}
					writecnt++;
					if (writecnt%8==0)
					{
						datapacket.insert(datapacket.end(), { udata.uiData });
					}
				}
			} while (!strstream.eof());
		}
	}
	if (writecnt%8!=0)
	{
		datapacket.insert(datapacket.end(), { udata.uiData });

	}

}
