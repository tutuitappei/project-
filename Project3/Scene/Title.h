#pragma once
#include "BaseScene.h"
#include"../Vector2.h"

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
	int Screensizex;
	int Screensizey;
};

