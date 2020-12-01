#pragma once
#include<vector>
#include "BaseScene.h"
#include"../input/Controller.h"
#include"../Obj/Player.h"
#include"../Obj/Block.h"
#include"../Map.h"
#include"../Vector2.h"

using ShareP = std::shared_ptr<Player>;

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
	void InstancePlayer(int x, int y, int PLID);

	int playernum = 0;
	int playerID = 0;

	unsigned int framCnt;
	unsigned int oldfCnt;

	int lendx = 0;
	int lengy = 0;
	std::pair<int, int> data;

	std::vector<ShareP> _playervec;

	Player _player;
	Block _block;
	Layer _layer;
	Map _map;
};

