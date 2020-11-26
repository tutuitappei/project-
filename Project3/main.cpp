#include<DxLib.h>
#include"Scene/Scenemanager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{		SetGraphMode(896, 640, 16);								// 640*480ÄŞ¯ÄA65536FÓ°ÄŞ‚Éİ’è
		ChangeWindowMode(true);									// true:window false:ÌÙ½¸Ø°İ

		SetWindowText("1916024");
		if (DxLib_Init() == -1)									// DX×²ÌŞ×Ø‚Ì‰Šú‰»ˆ—
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