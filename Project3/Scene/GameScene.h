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
	std::unique_ptr<Controller> controller;

	void HostUpdata(void);
	void GestUpdata(void);
	void OffLineUpdata(void);
	void SetDir(DIR dir);
	bool CheckAlive(int pnum);

	int playernum = 0;
	int playerID = 0;

	Vector2 imagepos[2];
	int imagechar[2][20];
	bool aliveFrag[2];

	int animCnt;
	unsigned int framCnt;
	unsigned int oldfCnt;

	int lendx = 0;
	int lengy = 0;
	std::pair<int, int> data;

	DIR _dir[2];

	Player _player;
	Block _block;
	Layer _layer;
	Map _map;
};

