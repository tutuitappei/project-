#pragma once
#include "BaseScene.h"
class GameScene :
    public BaseScene
{
public:
	GameScene();
	~GameScene();

	void Draw(void)override;
	void Init(void);
	void Updata(void)override;
};

