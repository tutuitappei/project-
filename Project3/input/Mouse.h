#pragma once
#include<array>
#include"../Vector2.h"
#include "Controller.h"
class Mouse :
	public Controller
{
public:

	ContType GetType(void) override;
	bool Setup(int no) override;

	void Update(void) override;

private:
	std::map<InputID, int>_inputTbl;

};

