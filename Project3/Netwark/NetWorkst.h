#pragma once

enum class NetworkMode
{
	OFF,
	HOST,
	GEST,
	MAX
};
enum class ActivState
{
	Non,		//misettei
	Wait,		//setuzokutaiki(host)
	Init,		//syokikatyuu
	Stanby,		//syokikajyouhousousinnzuminokaisimati(hosut)
	Play,		//ge-mutyuu
	OffLine	
};

class NetWorkst
{
public:
	NetWorkst();
	virtual ~NetWorkst();
	virtual NetworkMode GetMode(void) { return NetworkMode::OFF; };
	int GetHandle(void);
	bool GetActive(void);
	ActivState GetActivest(void);
	virtual ActivState ConnectHost(IPDATA hostip);
	virtual bool CheckNetwork(void);
	virtual bool CheckLostNetwork(void);
protected:
	const int _portnum = 8086;
	bool _active;
	ActivState _act;

	int _nethandle = 0;
	int _losthandle = 0;
};

