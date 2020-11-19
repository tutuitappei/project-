#pragma once
#include "BaseScene.h"
#include"../input/Controller.h"
#include"../Obj/Player.h"
#include"../Obj/Block.h"
#include"../Map.h"
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
	int playerID = 0;

	unsigned int framCnt;
	unsigned int oldfCnt;

	int lendx = 0;
	int lengy = 0;
	std::pair<int, int> data;

	Player _player;
	Block _block;
	Layer _layer;
	Map _map;
};

