#include<DxLib.h>
#include"Scene/Scenemanager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{		SetGraphMode(960, 480, 16);								// 640*480�ޯāA65536�FӰ�ނɐݒ�
		ChangeWindowMode(true);									// true:window false:�ٽ�ذ�

		SetWindowText("1916024");
		if (DxLib_Init() == -1)									// DXײ���؂̏���������
		{
			return false;
		}
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		lpScene.Run();
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}