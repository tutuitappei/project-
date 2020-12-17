#include<DxLib.h>
#include "GameOver.h"
#include "SceneManager.h"
#include"../Netwark/Network.h"

GameOver::GameOver()
{
	_iowa.first = _num;
	_iowa.second = _id;

	if (lpNetwark.GetNetWorkMode() == NetworkMode::HOST)
	{
		lpNetwark.SendMes(MesType::RESULT);
	}
	else if (lpNetwark.GetNetWorkMode() == NetworkMode::GEST)
	{
		lpNetwark.RecvMes();
	}
	else
	{

	}
}

GameOver::~GameOver()
{
}

void GameOver::Draw(void)
{
	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(50,(20*i)+30,0xffffff,"%dˆÊ",i+1);
		if (_iowa.second != -1)
		{
			DrawFormatString(100, (20 * i) + 30, 0xffffff, "ƒvƒŒƒCƒ„[%d", (_iowa.second/5)+1);
		}
		else
		{
			DrawFormatString(100, (20 * i) + 30, 0xffffff, "(^q^)");
		}
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
