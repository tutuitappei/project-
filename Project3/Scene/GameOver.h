#pragma once
#include "BaseScene.h"
class GameOver :
    public BaseScene
{
public:
	GameOver();
	~GameOver();

	void Draw(void)override;
	void Init(void);
	void Updata(void)override;
private:

};

