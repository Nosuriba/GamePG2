#include <DxLib.h>
#include "GameScene.h"
#include "GameBoard.h"
#include "MouseCtl.h"
#include "ImageMng.h"

#define SCREEN_SIZE_X (800)
#define SCREEN_SIZE_Y (600)

/* �ÓI�ȃ����o�ϐ��̒�` */
GameScene	  *GameScene::s_Instance;
std::once_flag GameScene::initFlag;
//std::unique_ptr<GameScene, s_Deleter> GameScene::s_Instance;

GameScene::GameScene()
{
	gScenePtr		= &GameScene::SysInit;
}

GameScene::~GameScene()
{
}

void GameScene::Create()
{
	/*s_Instance.reset(new GameScene());*/
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
		///* �{�^���������O�ɁA���݉������{�^���̏���
		//   �Â��{�^���̏��ɓn���Ă��� */
		//mousePush[PUSH_OLD] = mousePush[PUSH_NOW];
		//mousePush[PUSH_NOW] = DxLib::GetMouseInput();

		(this->*gScenePtr)();
	}
	LpGameScene.Destroy();
	DxLib_End();
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
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/sample.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "�^�C�g���V�[������", 0x000000);
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

	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD] & MOUSE_INPUT_LEFT))
	{
		boardPtr->Update(*mousePtr);
	}
	/*�}�E�X�����̍X�V���s��*/
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
