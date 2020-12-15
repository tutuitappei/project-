#pragma once
#include "BaseScene.h"
#include"../Vector2.h"
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

	int _id = 0;
	int _num = 0;

	std::pair<int, int> _iowa; //‡ˆÊ‚ÆƒvƒŒƒCƒ„[ID
};

