#include<DxLib.h>
#include "GameOver.h"
#include "SceneManager.h"
#include"../Netwark/Network.h"

GameOver::GameOver()
{
	_iowa.first = _num;
	_iowa.second = _id;
}

GameOver::~GameOver()
{
}

void GameOver::Draw(void)
{
	for (int i = 0; i < 5; i++)
	{
		//DrawFormatString();
	}
}

void GameOver::Init(void)
{
}

void GameOver::Updata(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		lpScene.ChangeScene(SCENE::TITLE);
		CloseNetWork(lpNetwark.GetNetHandle());
	}
}
