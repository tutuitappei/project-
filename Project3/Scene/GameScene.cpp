#include <iostream>
#include<DxLib.h>
#include <string>
#include<sstream>
#include "GameScene.h"
#include"../Vector2.h"
#include "SceneManager.h"
#include"../Netwark/Network.h"
#include"../_debug/_DebugConOut.h"
#include"../input/Pad.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Draw(void)
{
}

void GameScene::Init(void)
{
}

void GameScene::Updata(void)
{
	//GameSceneÇ…à⁄Ç∑
	//int lendx = 0;
	//int lengy = 0;
	//std::pair<int, int> data;
	//data.first = 0;
	//data.second = 0;
	//if (lpNetwark.GetNetWorkMode() == NetworkMode::HOST)
	//{
	//	if (!lpNetwark.CheckLost())
	//	{
	//		if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
	//		{
	//			NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
	//			imagepos.x += data.first;
	//			imagepos.y += data.second;
	//		}
	//	}
	//	else
	//	{
	//		lpNetwark.ChecLink();
	//	}
	//}
	//else if (lpNetwark.GetNetWorkMode() == NetworkMode::GEST)
	//{
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
	//	{
	//		lengy = 10;
	//	}
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
	//	{
	//		lengy = -10;
	//	}
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
	//	{
	//		lendx = -10;
	//	}
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
	//	{
	//		lendx = 10;
	//	}
	//	data.first = lendx;
	//	data.second = lengy;
	//	NetWorkSend(lpNetwark.GetNetHandle(), &data, sizeof(data));
	//}
	//else if (lpNetwark.GetNetWorkMode() == NetworkMode::OFF)
	//{
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
	//	{
	//		imagepos.y += 10;
	//	}
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
	//	{
	//		imagepos.y -= 10;
	//	}
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
	//	{
	//		imagepos.x -= 10;
	//	}
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
	//	{
	//		imagepos.x += 10;
	//	}
	//}
	//else
	//{
	//	TRACE("ÉQÅ[ÉÄíÜÇ…àŸèÌÇ™î≠ê∂ÇµÇ‹ÇµÇΩ\n");
	//}
}
