#include <DxLib.h>
#include "GameScene.h"
#include "GameBoard.h"
#include "MouseCtl.h"
#include "Player.h"
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

void GameScene::MakePlayer(void)
{
	playerList.push_back(std::make_shared<Player>());
}

void GameScene::NextPlayer(void)
{
	/*bool rtnFlag = false;*/

	player++;
	if (player == playerList.end())
	{
		player = playerList.begin();
	}
}

bool GameScene::AutoPassPlayer(void)
{
	player++;
	if (player == playerList.end())
	{
		player = playerList.begin();
	}

	if (boardPtr->CheckPutPieceFlag((*player)->pGetID()))
	{
		return true;
	}
	return false;
}

void GameScene::PutPieceST(void)
{
	pieceW = 0;
	pieceB = 0;

	/* �s�[�X�̐F���擾���āA���ꂼ��̌����J�E���g���Ă��� */
	for (int y = 0; y < boardPtr->GetDataSize().y; y++)
	{
		for (int x = 0; x < boardPtr->GetDataSize().x; x++)
		{
			if (boardPtr->CheckPutPieceST(x, y) == PIECE_W)
			{
				pieceW++;
			}
			else if (boardPtr->CheckPutPieceST(x, y) == PIECE_B)
			{
				pieceB++;
			}
			else{}
		}
	}
}

bool GameScene::WinJudge(void)
{
	return false;
}

int GameScene::SysInit()
{
	/* �V�X�e���̏��������I�������A�Q�[���̏����������鏈���p�֐��Ɉڍs���Ă��� */
	gScenePtr = &GameScene::TitleInit;

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
	/* �o�^���ꂽ�v���C���[�̏��������s���Ă��� */
	playerList.clear();					
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
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title.jpg")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "�^�C�g���V�[������", 0x000000);
	DxLib::ScreenFlip();

	return 0;
}

int GameScene::GameInit()
{
	gScenePtr = &GameScene::GameMain;
	boardPtr = std::make_unique<GameBoard>();
	boardPtr->PieceClear();
	boardPtr->SetPiece({ 3,3 }, true);			// true : �ʏ�̔����z�u, false : �����𔽓]���Ĕz�u
	PutPieceST();
	/* �v���C���[�̓o�^���s���Ă��� */
	MakePlayer();
	MakePlayer();
	player = playerList.begin();
	return 0;
}

int GameScene::GameMain()
{
	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		gScenePtr = &GameScene::ResultInit;
		boardPtr->PieceClear();
	}

	if ((*player)->TurnAct(*mousePtr, *boardPtr))
	{
		boardPtr->SetReverse(mousePtr->GetPoint(), (*player)->pGetID());
		PutPieceST();
		NextPlayer();
		
	}

	if (!boardPtr->CheckPutPieceFlag((*player)->pGetID()))
	{
		if (!AutoPassPlayer())
		{
			gScenePtr = &GameScene::ResultInit;
		}
	}
	mousePtr->Update();
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0,1.5f, 1.5f, "�Q�[���V�[������", 0xffffff);
	/* ���݃^�[���������s���Ă���s�[�X��`�悵�Ă��� */
	DxLib::DrawGraph(0, 50, (*player)->pGetID() == PIECE_W ? LpImageMng.ImgGetID("image/player1.png")[0] 
														   : LpImageMng.ImgGetID("image/player2.png")[0], true);
	DxLib::DrawFormatString(0, 200, 0xfffffff, "�� : %d", pieceW);
	DxLib::DrawFormatString(0, 230, 0xfffffff, "�� : %d", pieceB);
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
	/*PutPieceST();*/
	/*boardPtr->PieceClear();*/
	boardPtr->ResultPiece(pieceB, pieceW);

	mousePtr->Update();
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f,"���U���g�V�[������", 0xffffff);
	boardPtr->Draw();
	DxLib::ScreenFlip();
	
	return 0;
}

