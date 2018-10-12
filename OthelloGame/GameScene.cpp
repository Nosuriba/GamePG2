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
	playerList.push_back(std::make_shared<Player>(boardPtr->GetBoardSize()));
}

void GameScene::NextPlayer(void)
{
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

PIECE_ST GameScene::WinJudge(int pCntB, int pCntW)
{
	/* �s�[�X�̌����r���āA���������F�̏�Ԃ�Ԃ��悤�ɂ��Ă���*/
	if (pCntB < pCntW)
	{
		return PIECE_W;
	}
	else if (pCntB > pCntW)
	{
		return PIECE_B;
	}
	else if (pCntB == pCntW)
	{
		return PIECE_NON;
	}
	return PIECE_NON;
}

void GameScene::DrawWinner(PIECE_ST pState)
{
	if (pState == PIECE_B)
	{
		DxLib::DrawExtendString(250, 0, 2.5f, 2.5f, "���[��]�̏����Ȃ�", 0xfffacd);
	}
	else if (pState == PIECE_W)
	{
		DxLib::DrawExtendString(250, 0, 2.5f, 2.5f, "���[��]�̏����Ȃ�", 0xf0f8ff);
	}
	else
	{
		DxLib::DrawExtendString(300, 0, 2.5f, 2.5f, "��������...", 0xeeee00);
	}
}

int GameScene::SysInit()
{
	/* �V�X�e���̏��������I�������A�Q�[���̏��������s���悤�ɂ��Ă��� */
	gScenePtr = &GameScene::TitleInit;

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

	/* �^�C�g���̕`����s���Ă��� */
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title.jpg")[0], true);
	DxLib::DrawExtendString(0, 0, 2.5f, 2.5f, "�^�C�g��", 0xffff00);
	DxLib::ScreenFlip();

	return 0;
}

int GameScene::GameInit()
{
	gScenePtr	= &GameScene::GameMain;
	boardPtr	= std::make_unique<GameBoard>();
	boardPtr->PieceClear();
	boardPtr->StartPiece({ 3,3 }, true);			// true : �ʏ�̔����z�u, false : �����𔽓]���Ĕz�u
	PutPieceST();
	/* �v���C���[�̓o�^���s���Ă��� */
	MakePlayer();
	MakePlayer();
	player = playerList.begin();
	turnPLpiece = std::make_unique<GamePiece>(Vector2(0, 50), Vector2(0, 0), (*player)->pGetID());
	return 0;
}

int GameScene::GameMain()
{
	if ((*player)->TurnAct(*mousePtr, *boardPtr))
	{
		boardPtr->SetReverse(mousePtr->GetPoint(), (*player)->pGetID());
		PutPieceST();
		NextPlayer();
	}

	turnPLpiece->SetState((*player)->pGetID());

	if (!boardPtr->CheckPutPieceFlag((*player)->pGetID()))
	{
		if (!AutoPassPlayer())
		{
			boardPtr->PieceClear();
			gScenePtr = &GameScene::ResultInit;
		}
	}
	mousePtr->Update();
	/* �Q�[�����̏���`�悵�Ă��� */
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0,1.5f, 1.5f, "�Q�[�����[�h", 0xffffff);
	DxLib::DrawExtendFormatString(0, 170,1.3f, 1.3f, 0xfffffff, "�� : %d", pieceW);
	DxLib::DrawExtendFormatString(0, 200,1.3f, 1.3f, 0xfffffff, "�� : %d", pieceB);
	boardPtr->Draw();
	turnPLpiece->Draw();
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
	boardPtr->ResultPiece(pieceB, pieceW);
	mousePtr->Update();

	/* ���U���g�̏���`�悵�Ă��� */
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f,"���U���g", 0xffffff);
	boardPtr->Draw();
	DrawWinner(WinJudge(pieceB, pieceW));
	DxLib::DrawExtendFormatString(0, 170, 1.3f, 1.3f, 0xfffffff, "�� : %d", pieceW);
	DxLib::DrawExtendFormatString(0, 200, 1.3f, 1.3f, 0xfffffff, "�� : %d", pieceB);
	DxLib::ScreenFlip();
	
	return 0;
}

