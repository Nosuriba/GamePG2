#include <DxLib.h>
#include "GameScene.h"

GameScene *GameScene::s_Instance;

#define SCREEN_SIZE_X (600)
#define SCREEN_SIZE_Y (600)

GameScene::GameScene()
{
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

int GameScene::TitleInit()
{
	gScenePtr = &GameScene::TitleMain;
	return 0;
}


int GameScene::TitleMain()
{
	/*gScenePtr = &GameScene::GameInit;*/
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
	gScenePtr = &GameScene::ResultInit;
	return 0;
}

int GameScene::ResultInit()
{
	gScenePtr = &GameScene::ResultMain;
	return 0;
}

int GameScene::ResultMain()
{
	gScenePtr = &GameScene::TitleInit;
	DxLib::ClsDrawScreen();
	/*DxLib::DrawString();*/

	
	return 0;
}

