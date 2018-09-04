#include <DxLib.h>
#include "GameScene.h"
#include "ImageMng.h"

GameScene *GameScene::s_Instance;

#define SCREEN_SIZE_X (800)
#define SCREEN_SIZE_Y (600)

GameScene::GameScene()
{
	mousePush		= 0;
	mousePushOld	= 0;
	gScenePtr = &GameScene::SysInit;
}

GameScene::~GameScene()
{
}

void GameScene::Create()
{
	if (!s_Instance)
	{
		s_Instance = new GameScene();
	}
}

void GameScene::Destroy()
{
	if (s_Instance)
	{
		delete s_Instance;
	}
}

void GameScene::Run()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GameScene::UpDate();
	}
	DxLib_End();
}

int GameScene::UpDate()
{
	int SetMode		= (this->*gScenePtr)();
	mousePush		= DxLib::GetMouseInput();

	/* クリックした情報 */
	if (mousePush != mousePushOld)
	{
		mousePushOld = 0;
	}

	return 0;
}

int GameScene::SysInit()
{
	gScenePtr = &GameScene::TitleInit;

	DxLib::SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1701310_北川 潤一 : OthelloGame");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	return 0;
}

int GameScene::SysDestroy()
{
	return 0;
}

int GameScene::TitleInit()
{
	gScenePtr = &GameScene::TitleMain;
	return 0;
}


int GameScene::TitleMain()
{
	if (mousePush & MOUSE_INPUT_LEFT && mousePushOld != mousePush)
	{
		mousePushOld = DxLib::GetMouseInput();
		gScenePtr = &GameScene::GameInit;
	}
	DxLib::ClsDrawScreen();
	DxLib::DrawString(60, 60, "タイトルシーンだよ", 0xffffff);
	DxLib::ScreenFlip();

	return 0;
}

int GameScene::GameInit()
{
	gScenePtr = &GameScene::GameMain;
	return 0;
}

int GameScene::GameMain()
{
	if (mousePush & MOUSE_INPUT_LEFT && mousePushOld != mousePush)
	{
		mousePushOld = DxLib::GetMouseInput();
		gScenePtr = &GameScene::ResultInit;
	}
	DxLib::ClsDrawScreen();
	DxLib::DrawString(60, 60, "ゲームシーンだよ", 0xffffff);
	/*DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/sample.png")[0], true);*/
	DxLib::ScreenFlip();
	return 0;
}

int GameScene::GameDestroy()
{
	return 0;
}

int GameScene::ResultInit()
{
	gScenePtr = &GameScene::ResultMain;
	return 0;
}

int GameScene::ResultMain()
{
	if (mousePush & MOUSE_INPUT_LEFT && mousePushOld != mousePush)
	{
		mousePushOld = DxLib::GetMouseInput();
		gScenePtr = &GameScene::TitleInit;
	}
	DxLib::ClsDrawScreen();
	DxLib::DrawString(60, 60, "リザルトシーンだよ", 0xffffff);
	DxLib::ScreenFlip();
	
	return 0;
}