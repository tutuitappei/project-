#pragma once
#include<DxLib.h>
#include<memory>
#include"NetWorkst.h"

#define lpNetwark Netwark::GetInstance()

enum class MesType
{
	STANBY,
	GAME_S,
	POS
};
struct MesData
{
	MesType type;
	int data[2];
};

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
	void SendStanby(void);
	void SendStart(void);
	ActivState GetActiveST(void);
	ActivState ConnectHost(IPDATA hostip);
	bool ChecLink(void);

	//MesData _mesdata;
private:
	Netwark();
	~Netwark();

	std::unique_ptr <NetWorkst> _state;

	static Netwark* s_Instance;
};

