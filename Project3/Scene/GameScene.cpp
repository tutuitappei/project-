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
	InstancePlayer(,, playerID);
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

	for (auto&& player : _playervec)
	{
		player->DrawObj();
	}
}

void GameScene::Init(void)
{
	if ((lpNetwark.GetNetWorkMode() == NetworkMode::HOST) || (lpNetwark.GetNetWorkMode() == NetworkMode::GEST))
	{
		TRACE("�v���C���[�̐�%d�l\n", playernum);
		if ((lpNetwark.GetNetWorkMode() == NetworkMode::HOST))
		{
			playerID = 0;
		}
		else if ((lpNetwark.GetNetWorkMode() == NetworkMode::GEST))
		{
			playerID = lpNetwark.GetPlayerID();
		}
		else
		{
			TRACE("�z�X�g���Q�X�g���擾�ł��ĂȂ�����Ȃ��ł����`�B�₾�`www�B\n");
		}
	}
	else if (lpNetwark.GetNetWorkMode() == NetworkMode::OFF)
	{
		playernum = 1;
		playerID = 0;
		TRACE("�v���C���[�̐�%d�l\n", playernum);
	}
	else
	{
		TRACE("���݂̃l�b�g���[�N��Ԃ��擾�ł��ĂȂ�����Ȃ��ł����`�B�₾�`www�B\n");
	}
}

void GameScene::Updata(void)
{
	for (auto&& player : _playervec)
	{
		player->Update();
	}
	_block.Update();

	oldfCnt = framCnt;
	framCnt++;
}

void GameScene::InstancePlayer(int x, int y, int PLID)
{
	Vector2 pos = { x,y };

	auto id = PLID;
	_playervec.emplace(_playervec.begin(), std::make_unique<Player>(pos, id));
}


