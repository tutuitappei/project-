#include<DxLib.h>
#include "Mouse.h"

ContType Mouse::GetType(void)
{
	return ContType::Mouse;
}

bool Mouse::Setup(int no)
{

	//if (no <= 0)
	//{
	//	_inputTbl = {
	//		{InputID::Up,},
	//		{InputID::Down,},
	//		{InputID::Left,},
	//		{InputID::Right,},
	//		{InputID::Btn1,WM_LBUTTONDOWN},
	//		{InputID::Btn2,WM_RBUTTONDOWN}
	//	};
	//}
	//else
	//{
	//	_inputTbl = {
	//		{InputID::Up,},
	//		{InputID::Down,},
	//		{InputID::Left,},
	//		{InputID::Right,},
	//		{InputID::Btn1,WM_LBUTTONDOWN},
	//		{InputID::Btn2,WM_RBUTTONDOWN}
	//	};
	//}


	return true;
}

void Mouse::Update(void)
{
}
