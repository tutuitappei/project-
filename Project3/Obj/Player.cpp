#include<DxLib.h>
#include<functional>
#include"../Netwark/Network.h"
#include "Player.h"
#include"../_debug/_DebugConOut.h"
#include"../input/Pad.h"

Player::Player()
{
	_state.first = DIR::DOWN;
	_state.second = Animstate::Idel;
	aliveFrag[CheckID()] = true;

	animCnt = 0;

	Init();
}

Player::~Player()
{
}

void Player::Update(void)
{
	if (CheckAlive(playerID))
	{
		Move();
	}

	animCnt++;
}

void Player::DrawObj(void)
{
	DrawGraph(_pos.x, _pos.y, imagechar[CheckID()][(((animCnt / 10) % 4) * 5) + static_cast<int>(_dir[CheckID()])], true);
}

void Player::SetMap(void)
{
}

void Player::SetAnimSt(void)
{
}

void Player::Init(void)
{
	std::pair<int, int> data;

	//ホスト時
	data.first = _pos.x;
	data.second = _pos.y;
	NetWorkSend(lpNetwark.GetNetHandle(), &data, sizeof(data));

	//ゲスト時
	if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
	{
		NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
		_pos.x = data.first;
		_pos.y = data.second;
	}

	LoadDivGraph("image/bomberman.png", 20, 5, 4, 32, 50, imagechar[CheckID()]);

	controller = std::make_unique<Pad>();
	controller->Setup(CheckID());
}

void Player::SetID(int num)
{
	playerID = num;
}

int Player::CheckID(void)
{
	return playerID;
}

int Player::CheckDrop(unsigned int time, int num)
{
	return num / (time / 60);
}

bool Player::Alive(void)
{
	return false;
}

void Player::Move(void)
{

	if (CheckAnimSt(_state.second) && CheckMove(_state.first))
	{

	}
}

bool Player::CheckMove(DIR _dir)
{
	if (static_cast<int>(_dir) > static_cast<int>(DIR::RIGHT))
	{
		return false;
	}
	return true;
}

bool Player::CheckAnimSt(Animstate _as)
{
	if (_as == Animstate::Walk)
	{
		return true;
	}
	return false;
}

void Player::DefUpdata(void)
{
	std::pair<int, int> data;
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
	{
		_pos.y = 10;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
	{
		_pos.y = -10;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
	{
		_pos.x = -10;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
	{
		_pos.x = 10;
	}
	data.first = _pos.x;
	data.second = _pos.y;
	NetWorkSend(lpNetwark.GetNetHandle(), &data, sizeof(data));
}

void Player::NetUpdata(void)
{
	std::pair<int, int> data;

		if (!lpNetwark.CheckLost())
	{
		if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
		{
			NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
			_pos.x += data.first;
			_pos.y += data.second;
		}
	}
	else
	{
		lpNetwark.ChecLink();
	}
}

void Player::OutUpdata(void)
{
}

bool Player::CheckAlive(int pnum)
{
	aliveFrag[pnum] = true;
	if (CheckHitKey(KEY_INPUT_O))
	{
		aliveFrag[pnum] = false;
	}
	return aliveFrag[pnum];
}

void Player::SetDir(DIR dir)
{
	_dir[CheckID()] = dir;
}
