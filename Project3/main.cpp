#include<DxLib.h>
#include"Scene/Scenemanager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{		SetGraphMode(896, 640, 16);								// 640*480ﾄﾞｯﾄ、65536色ﾓｰﾄﾞに設定
		ChangeWindowMode(true);									// true:window false:ﾌﾙｽｸﾘｰﾝ
		
		SetWindowText("1916024");
		if (DxLib_Init() == -1)									// DXﾗｲﾌﾞﾗﾘの初期化処理
		{
			return false;
		}
		SetAlwaysRunFlag(true);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		lpScene.Run();
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}