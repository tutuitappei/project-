#pragma once
#include<map>
#include "BaseScene.h"
#include"../Vector2.h"
#include"../input/Controller.h"

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

	Vector2 imagepos;
	int _image;

};

