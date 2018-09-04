#include <DxLib.h>
#include "GameScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpCmdLine, int nCmdShow)
{
	LpGameScene.Run();
	LpGameScene.Destroy();
	return 0;
}