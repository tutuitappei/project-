#include<DxLib.h>
#include "Title.h"
#include"LoginScene.h"
#include"../Vector2.h"
#include "SceneManager.h"
#include"../_debug/_DebugConOut.h"
#include"../input/Pad.h"


Title::Title()
{
	
}

Title::~Title()
{
}

void Title::Draw(void)
{
}

void Title::Init(void)
{

}

void Title::Updata(void)
{
	lpScene.ChangeScene(SCENE::LOGIN);
}
