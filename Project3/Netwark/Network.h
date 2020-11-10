#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>
#include<chrono>
#include<thread>
#include"NetWorkst.h"

#define lpNetwark Netwark::GetInstance()

enum class MesType : unsigned char
{
	NON = 100,
	STANBY,
	GAME_S,
	TMX_SIZE,
	TMX_DATA,
	POS,
};
struct MesData
{
	MesType type;
	unsigned char next;		//データ送信が分割の場合に次があるかないか
	unsigned short sendID;	//分割送信時のナンバリング
	//unsigned int length;
	int data[2];
};
union Header
{
	MesData hd;
	unsigned int hamu[2];
};
union unionData
{
	unsigned int uiData;
	//int iData;
	//char cData[4];   //cData[0]→横のマス数:cData[1]→縦のマス数:cData[2]→レイヤーID:cData[3]→今は空の容量確保;
	int iData[2];
	char cData[8];
	long long lData;
};

using MesPacket = std::vector<unionData>;
using TmxBox = std::vector<char>;

class Netwark
{
public:
	static Netwark& GetInstance(void)
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new Netwark();
		}
		return *s_Instance;
	}

	void Updata(void);
	void Thread(void);

	IPDATA GetIp(void);
	bool SetNetWorkMode(NetworkMode mode);
	NetworkMode GetNetWorkMode(void);
	int GetNetHandle(void);
	bool GetActive(void);
	bool SendMes(MesType _mtype);
	bool SendMes(MesType _mtype, MesPacket _mpacket);
	void GetRevStanby(void);
	void GetRevStart(void);
	void SendStanby(void);
	void SendStart(void);
	ActivState GetActiveST(void);
	ActivState ConnectHost(IPDATA hostip);
	bool ChecLink(void);
	bool CheckLost(void);

	void Oneletter(void);

	void TmxChat(void);
	void TmxCheck(const char* filename);
	void TmxDataSend(void);
	void TmxDataRev(void);
private:
	Netwark();
	~Netwark();
	bool SendWait(void);
	void LetterSet(void);
	void LetterReceive(void);
	void SetHeader(Header head, MesPacket pack);
	void SendHeader(void);

	//unsigned int lengthd;
	//int count;
	//int volume;

	TmxBox _box;
	int bot = 0;
	std::unique_ptr <NetWorkst> _state;

	std::chrono::system_clock::time_point  start, end;

	static Netwark* s_Instance;
};

