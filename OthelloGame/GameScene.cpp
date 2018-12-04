#include <DxLib.h>
#include "GameScene.h"
#include "MouseCtl.h"
#include "TitleScene.h"
#include "PieceST.h"

std::unique_ptr<GameScene, GameScene::GameSceneDeleter> GameScene::s_Instance(new GameScene());

GameScene::GameScene() : screenSize(800, 600)
{
	SysInit();
}

GameScene::~GameScene()
{
	DxLib_End();
}

void GameScene::Run()
{
	gScene = std::make_unique<TitleScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		(*sysMouse).Update();
		gScene = (*gScene).Update(std::move(gScene), sysMouse);
	}
}

Vector2 GameScene::GetScreenSize(void)
{
	return Vector2(screenSize.x, screenSize.y);
}

int GameScene::UpDate()
{
	return 0;
}

int GameScene::SysInit()
{
	// �V�X�e���̏��������I�������A�Q�[���̏��������s���悤�ɂ��Ă��� 
	DxLib::SetGraphMode(screenSize.x, screenSize.y, 16);
	/*DxLib::SetWindowIconID();*/
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1701310_�k�� ���� : OthelloGame");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	sysMouse = std::make_shared<MouseCtl>();
	return 0;
}

int GameScene::SysDestroy()
{
	return 0;
}

