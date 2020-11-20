#include<DxLib.h>
#include "Keyboard1.h"


ContType Keyboard1::GetType(void)
{
	return ContType::Key;
}

bool Keyboard1::Setup(int no)
{
	if (no == 0)
	{
		_inputTbl = {
			{InputID::Up,KEY_INPUT_W},
			{InputID::Down,KEY_INPUT_S},
			{InputID::Left,KEY_INPUT_A},
			{InputID::Right,KEY_INPUT_D},
			{InputID::Btn1,KEY_INPUT_Q},
			{InputID::Btn2,KEY_INPUT_E}
		};
	}
	else
	{
			_inputTbl = {
				{InputID::Up,KEY_INPUT_NUMPAD8},
				{InputID::Down,KEY_INPUT_NUMPAD5},
				{InputID::Left,KEY_INPUT_NUMPAD4},
				{InputID::Right,KEY_INPUT_NUMPAD6},
				{InputID::Btn1,KEY_INPUT_NUMPAD7},
				{InputID::Btn2,KEY_INPUT_NUMPAD9}
			};
	}


	return true;
}

void Keyboard1::Update(void)
{
	GetHitKeyStateAll(_KeyData.data());
	for (auto id : InputID())
	{
		_data[id][static_cast<int>(Trg::Old)] = _data[id][static_cast<int>(Trg::Now)];
		_data[id][static_cast<int>(Trg::Now)] = _KeyData[_inputTbl[id]];
	}
}
