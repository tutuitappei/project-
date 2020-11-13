#include "Player.h"

Player::Player()
{
	_state.first = DIR::DOWN;
	_state.second = Animstate::Idel;

	Init();
}

Player::~Player()
{
}

void Player::Update(void)
{
	Move();
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
}

int Player::CheckID()
{
	return 0;
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
