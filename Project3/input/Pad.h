#pragma once
#include<array>
#include"../Vector2.h"
#include "Controller.h"
class Pad :
	public Controller
{
public:

	ContType GetType(void) override;
	bool Setup(int no) override;

	void Update(void) override;
private:
	std::array<char, 28>_PadData;		//キーのデータ
	std::map<InputID, int>_inputTbl;	//インプット用テーブル
};

