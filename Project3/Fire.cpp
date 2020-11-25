#include<DxLib.h>
#include "Fire.h"

Fire::Fire()
{
	_longFire = DefFire;
	Init();
}

Fire::~Fire()
{
}

void Fire::Update(void)
{
}

void Fire::Draw(void)
{
}

void Fire::AddFire(int a)
{
	_longFire += a;
}

void Fire::Init(void)
{
	LoadDivGraph("fire.png", 12, 3, 4, 20, 20, &fireimage, true);
}

void Fire::timeclock(void)
{
}
