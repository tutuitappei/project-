#include<DxLib.h>
#include "Pad.h"

ContType Pad::GetType(void)
{
	return ContType();
}

bool Pad::Setup(int no)
{
	if (no == 0)
	{
		_inputTbl = {
			{InputID::Up,PAD_INPUT_UP},
			{InputID::Down,PAD_INPUT_DOWN},
			{InputID::Left,PAD_INPUT_LEFT},
			{InputID::Right,PAD_INPUT_RIGHT},
			{InputID::Btn1,PAD_INPUT_1},
			{InputID::Btn2,PAD_INPUT_2}
		};
	}
	if (no == 1)
	{
		_inputTbl = {
			{InputID::Up,PAD_INPUT_UP},
			{InputID::Down,PAD_INPUT_DOWN},
			{InputID::Left,PAD_INPUT_LEFT},
			{InputID::Right,PAD_INPUT_RIGHT},
			{InputID::Btn1,PAD_INPUT_1},
			{InputID::Btn2,PAD_INPUT_2}
		};
	}

	return true;
}

void Pad::Update(void)
{
	for (auto id : InputID())
	{
		_data[id][static_cast<int>(Trg::Old)] = _data[id][static_cast<int>(Trg::Now)];
		_data[id][static_cast<int>(Trg::Now)] = (GetJoypadInputState(DX_INPUT_PAD1)&_inputTbl[id]);
	}
}
