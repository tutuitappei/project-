#pragma once
#include<map>
#include "BaseScene.h"
#include"../Vector2.h"
#include"../Map.h"


enum class Updatamode
{
	SetNetWork,
	SetHostIP,
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
	void SetHostIP(void);

	IPDATA hostIp;
};

