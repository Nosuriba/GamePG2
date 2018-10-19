#include <DxLib.h>
#include "GameScene.h"
#include "GameBoard.h"
#include "MouseCtl.h"
#include "Player.h"
#include "ImageMng.h"
#include "TitleScene.h"

#define SCREEN_SIZE_X (800)
#define SCREEN_SIZE_Y (600)

/* �ÓI�ȃ����o�ϐ��̒�` */
std::unique_ptr<GameScene, GameScene::GameSceneDeleter> GameScene::s_Instance(new GameScene());

GameScene::GameScene()
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
		gScene = (*gScene).Update(std::move(gScene), *mousePtr);
	}
}

Vector2 GameScene::GetScreenSize(void)
{
	return Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

int GameScene::UpDate()
{
	return 0;
}

int GameScene::SysInit()
{
	/* �V�X�e���̏��������I�������A�Q�[���̏��������s���悤�ɂ��Ă��� */
	DxLib::SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	/*DxLib::SetWindowIconID();*/
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1701310_�k�� ���� : OthelloGame");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	mousePtr = std::make_unique<MouseCtl>();
	return 0;
}

int GameScene::SysDestroy()
{
	return 0;
}

