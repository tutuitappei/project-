#pragma once
#include "BaseScene.h"
#include"../input/Controller.h"
#include"../Map.h"
#include"../Vector2.h"

enum class DIR
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	DEAD,
	MAX
};

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
	bool CheckAlive(void);

	int playernum = 0;
	int playerID = 0;

	Vector2 imagepos[2];
	int imagechar[2][20];
	bool aliveFrag;

	int animCnt;

	int lendx = 0;
	int lengy = 0;
	std::pair<int, int> data;

	DIR _dir[2];

	Layer _layer;
	Map _map;
};

