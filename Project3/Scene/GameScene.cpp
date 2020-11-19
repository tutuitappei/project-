#include <iostream>
#include<DxLib.h>
#include <string>
#include<sstream>
#include "GameScene.h"
#include "SceneManager.h"
#include"../Netwark/Network.h"
#include"../_debug/_DebugConOut.h"
#include"../input/Pad.h"

GameScene::GameScene()
{
	data.first = 0;
	data.second = 0;
	oldfCnt = 0;
	framCnt = 0;
	Init();
}

GameScene::~GameScene()
{
}

void GameScene::Draw(void)
{
	_map.DrawMap(Layer::Bg);
	_map.DrawMap(Layer::Item);
	_map.DrawMap(Layer::Obj);
	_map.DrawMap(Layer::Char);

	_player.DrawObj();
}

void GameScene::Init(void)
{
	if ((lpNetwark.GetNetWorkMode() == NetworkMode::HOST) || (lpNetwark.GetNetWorkMode() == NetworkMode::GEST))
	{
		playernum = 2;
		TRACE("プレイヤーの数%d人\n", playernum);
		if ((lpNetwark.GetNetWorkMode() == NetworkMode::HOST))
		{
			playerID = 0;
		}
		else if ((lpNetwark.GetNetWorkMode() == NetworkMode::GEST))
		{
			playerID = 1;
		}
		else
		{
			TRACE("ホストかゲストを取得できてないじゃないですか～。やだ～www。\n");
		}
	}
	else if (lpNetwark.GetNetWorkMode() == NetworkMode::OFF)
	{
		playernum = 1;
		playerID = 0;
		TRACE("プレイヤーの数%d人\n", playernum);
	}
	else
	{
		TRACE("現在のネットワーク状態を取得できてないじゃないですか～。やだ～www。\n");
	}
}

void GameScene::Updata(void)
{
	_player.Update();
	_block.Update();

	oldfCnt = framCnt;
	framCnt++;
}


