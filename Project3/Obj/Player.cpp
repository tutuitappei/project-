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
}

void Player::DrawObj(void)
{
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

void Player::HostUpdata(void)
{
}

void Player::GestUpdata(void)
{
}

void Player::OffLineUpdata(void)
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