#pragma once
#include<map>
#include<functional>
#include "BaseScene.h"
#include"../Vector2.h"
#include"../Map.h"

#include"../TimeKeeper.h"


enum class Updatamode
{
	SetNetWork,
	SetHostIP,
	SetOldIP,
	StartInit,
	Play
};


class LoginScene :
    public BaseScene
{
public:
	LoginScene();
	~LoginScene();

	void Draw(void)override;
	void Init(void);
	void Updata(void)override;
private:

	int Screensizex;
	int Screensizey;

	int _id = 0;

	Vector2 imagepos;
	int _image;

	Layer _layer;
	Map _map;

	//êVãK
	bool SetHostIP(void);
	bool SetNetwork(void);
	bool StartInit(void);
	bool Played(void);
	bool SetOldIP(void);

	bool thFlag;

	std::map<Updatamode, std::function<bool(void)>> updatefunc;

	Updatamode key;
	IPDATA oldhostIp;
	IPDATA hostIp;
};

