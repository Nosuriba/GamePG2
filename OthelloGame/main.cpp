#include <DxLib.h>
#include <iostream>
#include "GameScene.h"

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpCmdLine, int nCmdShow)
//{
//	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
//	{
//		
//	}
//	
//	DxLib_End();
//	return 0;
//}

int main()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GameScene::GetInstance().Create();
	}

	DxLib_End();
	return 0;
}