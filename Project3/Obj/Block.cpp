#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::Update(void)
{
}

void Block::DrawObj(void)
{
}

Vector2 Block::ChangPosTile(Vector2 pos)
{
	_changpos.x = pos.x / 32;
	_changpos.y = pos.y / 32;
	return _changpos;
}

void Block::SetMap(void)
{
}

void Block::Init(void)
{
}

bool Block::Alive(void)
{
	return false;
}

void Block::Break(void)
{
}
