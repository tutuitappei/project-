#pragma once
#include"../Vector2.h"
class Obj
{
public:
	Obj();
	~Obj();

	virtual void Update(void);
	virtual void DrawObj(void);
	virtual void ChangPosTile(Vector2 pos);
private:
};

