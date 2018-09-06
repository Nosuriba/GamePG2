#include <DxLib.h>
#include "GameScene.h"
#include "ImageMng.h"

#define SCREEN_SIZE_X (800)
#define SCREEN_SIZE_Y (600)

std::once_flag GameScene::initFlag;
GameScene	  *GameScene::s_Instance;

GameScene::GameScene()
{
	mousePush		= 0;
	mousePushOld	= 0;
	gScenePtr		= &GameScene::SysInit;
}

GameScene::~GameScene()
{
}

void GameScene::Create()
{
	s_Instance = new GameScene();
}

void GameScene::Destroy()
{
	if (s_Instance)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

void GameScene::Run()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		mousePushD[PUSH_OLD] = mousePushD[PUSH_NOW];
		mousePushD[PUSH_NOW] = DxLib::GetMouseInput();
		GameScene::UpDate();
	}
	DxLib_End();
}

int GameScene::UpDate()
{
	int setScene	= (this->*gScenePtr)();
	mousePush		= DxLib::GetMouseInput();

	/* マウスをクリックしていない時、 */
	if (mousePush == 0)
	{
		mousePushOld = 0;
	}

	return setScene;
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
	/*if (mousePush & MOUSE_INPUT_LEFT && mousePushOld != mousePush)
	{
		mousePushOld = mousePush;
		gScenePtr	 = &GameScene::GameInit;
	}
*/
	if (mousePushD[PUSH_NOW] & (~mousePushD[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		mousePushOld = mousePush;
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
		mousePushOld = mousePush;
		gScenePtr	 = &GameScene::ResultInit;
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
		gScenePtr	 = &GameScene::TitleInit;
	}
	DxLib::ClsDrawScreen();
	DxLib::DrawString(60, 60, "リザルトシーンだよ", 0xffffff);
	DxLib::ScreenFlip();
	
	return 0;
}