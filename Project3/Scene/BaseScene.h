#pragma once
#include<memory>

class BaseScene
{
public:
	BaseScene();
	~BaseScene();

	virtual void Updata() = 0;
	virtual void Draw() = 0;


private:
};

