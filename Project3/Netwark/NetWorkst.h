#pragma once

enum class NetworkMode
{
	OFF,
	HOST,
	GEST,
	MAX,
};

class NetWorkst
{
public:
	NetWorkst();
	virtual ~NetWorkst();
	virtual NetworkMode GetMode(void) { return NetworkMode::OFF; };
	int GetHandle(void);
	bool GetActive(void);
	virtual bool ConnectHost(IPDATA hostip);
	virtual bool CheckNetwork(void);
protected:
	const int _portnum = 8086;
	bool _active;

	int _nethandle = 0;
};

