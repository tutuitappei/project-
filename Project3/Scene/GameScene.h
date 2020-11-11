#pragma once
#include "BaseScene.h"
#include"../Vector2.h"
class GameScene :
    public BaseScene
{
public:
	GameScene();
	~GameScene();

	void Draw(void)override;
	void Init(void);
	void Updata(void)override;
private:
	int playernum = 0;
	Vector2 imagepos;
	Vector2 _imagepos[2];
	int imagechar[2][4][4];
};

