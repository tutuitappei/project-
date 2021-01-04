#include<DxLib.h>
#include"../Netwark/Network.h"
#include "Bomb.h"


Bomb::Bomb()
{
	bpos = {0,0};
	bomflag = false;
	playerID = 0;
	hostID = 0;
	bomdid = 0;
	Init();
}

Bomb::Bomb(Vector2 vec, int id)
{
	bpos = vec;
	bomflag = false;
	playerID = id;
	hostID = 0;
	bomdid++;
	Init();
}

Bomb::~Bomb()
{
}

void Bomb::Update(void)
{
}

void Bomb::DrawObj(void)
{
	ChangPosTile(bpos);
	DrawGraph(_changpos.x * 32, _changpos.y * 32, bombimage[0], true);
}

void Bomb::ChangPosTile(Vector2 pos)
{
	_changpos.x = pos.x / 32;
	_changpos.y = pos.y / 32;
}

bool Bomb::CheckAlive(void)
{
	return false;
}

void Bomb::Init(void)
{
	LoadDivGraph("image/bomb.png",14,2,7,32,32, bombimage,true);
	start = lpTime.GetTime();
}

bool Bomb::BomClash(void)
{
	recently =lpTime.GetTime();
	if (lpTime.SystemTimemilli(start, recently) >= static_cast<long long>(3000))
	{
		bomflag = true;
	}
	return bomflag;
}
