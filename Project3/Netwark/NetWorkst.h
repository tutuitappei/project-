#pragma once
#include<list>
#include<string>

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

struct PlayerData
{
	int handle;
	unsigned int playerID;
	int state;
};

using ListInt = std::list<std::tuple<int, unsigned int, int>>;

class NetWorkst
{
public:
	NetWorkst();
	virtual ~NetWorkst();
	virtual NetworkMode GetMode(void) { return NetworkMode::OFF; };
	void SetHandle(void);
	void SetPlayerID(void);
	void SetState(void);
	int GetHandle(void);
	int GetPlayerID(void);
	bool GetActive(void);
	ActivState GetActivest(void);
	virtual ActivState ConnectHost(IPDATA hostip);
	virtual bool CheckNetwork(void);
	virtual bool CheckLostNetwork(void);


protected:
	const int _portnum = 8086;
	bool _active;
	ActivState _act;

	ListInt PlayerList;
	PlayerData _Pdata;


	int _nethandle = 0;
	int _losthandle = 0;
};

