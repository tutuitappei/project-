#pragma once
#include<DxLib.h>
#include<memory>
#include"NetWorkst.h"

#define lpNetwark Netwark::GetInstance()

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

	bool GetActive(void);
	bool ConnectHost(IPDATA hostip);
private:
	Netwark();
	~Netwark();

	std::unique_ptr <NetWorkst> _state;

	static Netwark* s_Instance;
};

