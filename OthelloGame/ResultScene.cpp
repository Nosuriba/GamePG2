#include "ResultScene.h"
#include "MouseCtl.h"
#include "GameBoard.h"

ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

bool ResultScene::Update()
{
	return 0;
}

void ResultScene::Draw()
{
}

PIECE_ST ResultScene::WinJudge(int pCntB, int pCntW)
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

void ResultScene::DrawWinner(PIECE_ST pState)
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

int ResultScene::ResultInit()
{
	/*gScenePtr = &GameScene::ResultMain;*/
	return 0;
}

int ResultScene::ResultMain()
{
	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		/*playerList.clear();*/
		/*gScenePtr = &GameScene::TitleInit;*/
	}
	boardPtr->ResultPiece(pieceB, pieceW);
	mousePtr->Update();

	/* ���U���g�̏���`�悵�Ă��� */
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "���U���g", 0xffffff);
	boardPtr->Draw();
	DrawWinner(WinJudge(pieceB, pieceW));
	/* �s�[�X�̌���`�悵�Ă��镔�����C�����Ă���(�֐������Ă����̂����肩��)*/
	DxLib::DrawExtendFormatString(0, 170, 1.3f, 1.3f, 0xfffffff, "�� : %d", pieceW);
	DxLib::DrawExtendFormatString(0, 200, 1.3f, 1.3f, 0xfffffff, "�� : %d", pieceB);
	DxLib::ScreenFlip();

	return 0;
}

