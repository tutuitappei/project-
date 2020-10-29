#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>
#include<chrono>
#include"NetWorkst.h"

#define lpNetwark Netwark::GetInstance()

enum class MesType : unsigned char
{
	STANBY,
	GAME_S,
	TMX_SIZE,
	TMX_DATA,
	POS,
};
struct MesData
{
	MesType type;
	unsigned short shortd;
	unsigned char chard;
	int data[2];
};
union unionData
{
	char cData[8];
	int iData[2];
	long long lData;
};


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

	IPDATA GetIp(void);
	bool SetNetWorkMode(NetworkMode mode);
	NetworkMode GetNetWorkMode(void);
	int GetNetHandle(void);
	bool GetActive(void);
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

	TmxBox _box;
	int bot = 0;
	std::unique_ptr <NetWorkst> _state;

	std::chrono::system_clock::time_point  start, end;

	static Netwark* s_Instance;
};

