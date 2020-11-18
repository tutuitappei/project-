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
	animCnt = 0;
	oldfCnt = 0;
	framCnt = 0;
	Init();
}

GameScene::~GameScene()
{
}

void GameScene::Draw(void)
{
	
	for (int a = 0; a < playernum; a++)
	{
		//auto animmode = ;
		DrawGraph(imagepos[a].x, imagepos[a].y, imagechar[a][(((animCnt / 10) % 4) * 5) + static_cast<int>(_dir[a])], true);
	}

	_map.DrawMap(Layer::Bg);
	_map.DrawMap(Layer::Item);
	_map.DrawMap(Layer::Obj);
	_map.DrawMap(Layer::Char);
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

	_dir[playerID] = DIR::DOWN;
	for (int a = 0; a < playernum; a++)
	{
		LoadDivGraph("image/bomberman.png", 20, 5, 4, 32, 50, imagechar[a]);
	}

	controller = std::make_unique<Pad>();
	controller->Setup(playernum);
}

void GameScene::Updata(void)
{
	//GameSceneに移す

	//if (lpNetwark.GetNetWorkMode() == NetworkMode::HOST)
	//{
	//	if (!lpNetwark.CheckLost())
	//	{
	//		if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
	//		{
	//			NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
	//			imagepos[1].x += data.first;
	//			imagepos[1].y += data.second;
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
	//		SetDir(DIR::DOWN);
	//		imagepos[0].y += 10;
	//	}
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
	//	{
	//		SetDir(DIR::UP);
	//		imagepos[0].y -= 10;
	//	}
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
	//	{
	//		SetDir(DIR::LEFT);
	//		imagepos[0].x -= 10;
	//	}
	//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
	//	{
	//		SetDir(DIR::RIGHT);
	//		imagepos[0].x += 10;
	//	}
	//}
	//else
	//{
	//	TRACE("ゲーム中に異常が発生しました\n");
	//}
	_player.Update();
	_block.Update();

	oldfCnt = framCnt;
	animCnt++;
	framCnt++;
}
//
//void GameScene::HostUpdata(void)
//{
//	if (!lpNetwark.CheckLost())
//	{
//		if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
//		{
//			NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
//			if ((imagepos[1].x != data.first)||(imagepos[1].y != data.second))
//			{
//				imagepos[1].x += data.first;
//				imagepos[1].y += data.second;
//			}
//		}
//	}
//	else
//	{
//		lpNetwark.ChecLink();
//	}
//
//
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
//	{
//		imagepos[0].y += 10;
//		lengy = 10;
//	}
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
//	{
//		imagepos[0].y -= 10;
//		lengy = -10;
//	}
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
//	{
//		imagepos[0].x -= 10;
//		lendx = -10;
//	}
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
//	{
//		imagepos[0].x += 10;
//		lendx = 10;
//	}
//	data.first = lendx;
//	data.second = lengy;
//	NetWorkSend(lpNetwark.GetNetHandle(), &data, sizeof(data));
//}
//
//void GameScene::GestUpdata(void)
//{
//	if (!lpNetwark.CheckLost())
//	{
//		if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
//		{
//			NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
//			if ((imagepos[0].x != data.first) || (imagepos[0].y != data.second))
//			{
//				imagepos[0].x += data.first;
//				imagepos[0].y += data.second;
//			}
//
//		}
//	}
//	else
//	{
//		lpNetwark.ChecLink();
//	}
//
//
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
//	{
//		imagepos[1].y += 10;
//		lengy = 10;
//	}
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
//	{
//		imagepos[1].y -= 10;
//		lengy = -10;
//	}
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
//	{
//		imagepos[1].x -= 10;
//		lendx = -10;
//	}
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
//	{
//		imagepos[1].x += 10;
//		lendx = 10;
//	}
//	data.first = lendx;
//	data.second = lengy;
//	NetWorkSend(lpNetwark.GetNetHandle(), &data, sizeof(data));
//}
//
//void GameScene::OffLineUpdata(void)
//{
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
//	{
//		SetDir(DIR::DOWN);
//		imagepos[0].y += 10;
//	}
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
//	{
//		SetDir(DIR::UP);
//		imagepos[0].y -= 10;
//	}
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
//	{
//		SetDir(DIR::LEFT);
//		imagepos[0].x -= 10;
//	}
//	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
//	{
//		SetDir(DIR::RIGHT);
//		imagepos[0].x += 10;
//	}
//}

void GameScene::SetDir(DIR dir)
{
	for (int a = 0; a < playernum; a++)
	{
		_dir[a] = dir;
	}
}

