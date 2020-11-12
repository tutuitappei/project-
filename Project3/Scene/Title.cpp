#include<DxLib.h>
#include "Title.h"
#include"LoginScene.h"
#include"../Vector2.h"
#include "SceneManager.h"
#include"../_debug/_DebugConOut.h"
#include"../input/Pad.h"


Title::Title()
{
	Init();
}

Title::~Title()
{
}

void Title::Draw(void)
{
	GetDrawScreenSize(&Screensizex, &Screensizey);
}

void Title::Init(void)
{
	Screensizex = 0;
	Screensizey = 0;
}

void Title::Updata(void)
{
	lpScene.ChangeScene(SCENE::LOGIN);
}
