#include "GameOver.h"
#include "SceneManager.h"

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

void GameOver::Draw(void)
{
}

void GameOver::Init(void)
{
}

void GameOver::Updata(void)
{
	lpScene.ChangeScene(SCENE::TITLE);
}
