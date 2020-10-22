#pragma once
#include<map>
#include "BaseScene.h"
#include"../Vector2.h"
#include"../input/Controller.h"
#include"../Map.h"

enum class Updatamode
{
	SetNetWork,
	SetHostIP,
	StartInit,
	Play
};


class Title:
	public BaseScene
{
public:
	Title();
	~Title();

	void Draw(void)override;
	void Init(void);
	void Updata(void)override;
private:
	std::unique_ptr<Controller> controller;

	int Screensizex;
	int Screensizey;


	int _id = 0;

	Vector2 imagepos;
	int _image;

	Map _map;
};

