#include "ResultScene.h"
#include "TitleScene.h"
#include "MouseCtl.h"
#include "GameBoard.h"

ResultScene::ResultScene(std::shared_ptr<GameBoard> gBoard)
{
	boardPtr = gBoard;
	piece	 = (*boardPtr).GetPieceCnt();
}

ResultScene::~ResultScene()
{
}

PIECE_ST ResultScene::WinJudge(PutPiece piece)
{
	/* �s�[�X�̌����r���āA���������s�[�X�̏�Ԃ�Ԃ��悤�ɂ��Ă���*/
	if (piece.b < piece.w)
	{
		return PIECE_W;
	}
	else if (piece.b > piece.w)
	{
		return PIECE_B;
	}
	else if (piece.b == piece.w)
	{
		return PIECE_NON;
	}
	return PIECE_NON;
}

void ResultScene::DrawWinner(PIECE_ST pState)
{
	/* �����ŏ��҂̃s�[�X�̏�Ԃ��擾���A
	   �`����s���Ă��� */
	if (pState == PIECE_B)
	{
		DxLib::DrawExtendString(240, 0, 2.5f, 2.5f, "���[��]�̏����Ȃ�", 0xfffacd);
	}
	else if (pState == PIECE_W)
	{
		DxLib::DrawExtendString(240, 0, 2.5f, 2.5f, "���[��]�̏����Ȃ�", 0xf0f8ff);
	}
	else
	{
		/* ���҂����܂�Ȃ��������̕`�� */
		DxLib::DrawExtendString(300, 0, 2.5f, 2.5f, "��������...", 0xeeee00);
	}
}



void ResultScene::Init()
{
}

unique_scene ResultScene::Update(unique_scene own, MouseCtl& mouse)
{
	mouse.Update();
	/* �E�N���b�N���������A�^�C�g���̃V�[���Ɉڍs���Ă���*/
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		return std::make_unique<TitleScene>();
	}
	/* �s�[�X�̕��ёւ����s���Ă��� */
	(*boardPtr).ResultPiece(piece);
	
	/* ���U���g�̏���`�悵�Ă��� */
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "���U���g", 0xffffff);
	(*boardPtr).Draw();
	DrawWinner(WinJudge(piece));
	DxLib::DrawExtendFormatString(700, 450, 1.5f, 1.5f, 0xeeee00, "��: %d", piece.w);
	DxLib::DrawExtendFormatString(25, 450, 1.5f, 1.5f, 0xeeee00, "��: %d", piece.b);
	DxLib::ScreenFlip();

	return std::move(own);
}