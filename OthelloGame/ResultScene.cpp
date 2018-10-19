#include "ResultScene.h"
#include "TitleScene.h"
#include "MouseCtl.h"
#include "GameBoard.h"

ResultScene::ResultScene(std::shared_ptr<GameBoard> gBoard)
{
	/* ����shared�œ������Ă݂�(��������unique�ɕς��Ă���)*/
	boardPtr = gBoard;
	piece	 = boardPtr->GetPieceCnt();
}


ResultScene::~ResultScene()
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



void ResultScene::Init()
{
}

unique_scene ResultScene::Update(unique_scene own, MouseCtl& mouse)
{
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		return std::make_unique<TitleScene>();
	}
	boardPtr->ResultPiece(piece.b, piece.w);
	/* �}�E�X�̃N���b�N���������u�ԂɂȂ��Ă��Ȃ��̂ŁA�����̏C�����s��*/
	mouse.Update();

	/* ���U���g�̏���`�悵�Ă��� */
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "���U���g", 0xffffff);
	boardPtr->Draw();
	DrawWinner(WinJudge(piece.b, piece.w));
	DxLib::DrawExtendFormatString(0, 170, 1.3f, 1.3f, 0xfffffff, "�� : %d", piece.w);
	DxLib::DrawExtendFormatString(0, 200, 1.3f, 1.3f, 0xfffffff, "�� : %d", piece.b);
	DxLib::ScreenFlip();

	return std::move(own);
}