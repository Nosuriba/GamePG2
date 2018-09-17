#include <DxLib.h>
#include "GameScene.h"
#include "GameBoard.h"
#include "MouseCtl.h"
#include "ImageMng.h"

#define SCREEN_SIZE_X (800)
#define SCREEN_SIZE_Y (600)

/* �ÓI�ȃ����o�ϐ��̒�` */
std::unique_ptr<GameScene, GameScene::GameSceneDeleter> GameScene::s_Instance(new GameScene());

GameScene::GameScene()
{
	gScenePtr		= &GameScene::SysInit;
}

GameScene::~GameScene()
{
	DxLib_End();
}

void GameScene::Run()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		(this->*gScenePtr)();
	}
	/*GameSceneDeleter(s_Instance);*/
}

int GameScene::UpDate()
{
	return 0;
}

int GameScene::SysInit()
{
	/* �V�X�e���̏��������I�������A�Q�[���̏����������鏈���p�֐��Ɉڍs���Ă���
	*/
	gScenePtr = &GameScene::GameInit;

	/* �\������E�B���h�E�̏����ݒ���s���Ă��� */
	DxLib::SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
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

int GameScene::TitleInit()
{
	gScenePtr = &GameScene::TitleMain;
	return 0;
}

int GameScene::TitleMain()
{
	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		gScenePtr = &GameScene::GameInit;
	}
	mousePtr->Update();
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(100, 50, LpImageMng.ImgGetID("image/sample2.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "�^�C�g���V�[������", 0xffffff);
	DxLib::ScreenFlip();

	return 0;
}

int GameScene::GameInit()
{
	boardPtr = std::make_unique<GameBoard>();
	gScenePtr = &GameScene::GameMain;
	return 0;
}

int GameScene::GameMain()
{

	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		gScenePtr	 = &GameScene::ResultInit;
	}
	/*�}�E�X�����̍X�V���s��*/
	boardPtr->Update(*mousePtr);		// �}�E�X�̃N���b�N�����ƕ`��ʒu�̏���
	mousePtr->Update();
	DxLib::ClsDrawScreen();
	DxLib::DrawExtendString(0, 0,1.5f, 1.5f, "�Q�[���V�[������", 0xffffff);
	boardPtr->Draw();
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
	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		gScenePtr	 = &GameScene::TitleInit;
	}

	mousePtr->Update();
	DxLib::ClsDrawScreen();
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f,"���U���g�V�[������", 0xffffff);
	DxLib::ScreenFlip();
	
	return 0;
}
