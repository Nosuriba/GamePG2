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

void ResultScene::Init()
{
}

PIECE_ST ResultScene::WinJudge(PutPiece piece)
{
	if (piece.b < piece.w)			// ���̏���
	{
		return PIECE_ST::W;
	}
	else if (piece.b > piece.w)		// ���̏���
	{
		return PIECE_ST::B;
	}
	else if (piece.b == piece.w)	// ��������
	{
		return PIECE_ST::NON;
	}
	return PIECE_ST::NON;
}

void ResultScene::DrawWinner(PIECE_ST pState)
{
	// ���҂̕`��
	if (pState == PIECE_ST::B)
	{
		DxLib::DrawExtendString(240, 5, 2.5f, 2.5f, "���[��]�̏����Ȃ�", 0xfffacd);
	}
	else if (pState == PIECE_ST::W)
	{
		DxLib::DrawExtendString(240, 5, 2.5f, 2.5f, "���[��]�̏����Ȃ�", 0xf0f8ff);
	}
	else
	{
		// ���������̎��̕`��
		DxLib::DrawExtendString(300, 5, 2.5f, 2.5f, "��������...", 0xeeee00);
	}
}

unique_scene ResultScene::Update(unique_scene own, mouse_shared sysMouse)
{
	// �E�N���b�N���������A�^�C�g���̃V�[���Ɉڍs���Ă���
	if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		return std::make_unique<TitleScene>();
	}
	// �s�[�X�̕��ёւ����s���Ă��� 
	(*boardPtr).ResultPiece(piece);

	// ���U���g�̏���`�悵�Ă��� 
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	(*boardPtr).Draw();
	DrawWinner(WinJudge(piece));
	// DxLib::DrawExtendString(60, 300, 2.2f, 2.2f, "���N���b�N�������ƃ^�C�g����ʂɖ߂��", 0xffff00);
	DxLib::DrawExtendFormatString(700, 450, 1.5f, 1.5f, 0xeeee00, "��: %d", piece.w);
	DxLib::DrawExtendFormatString(25 , 450, 1.5f, 1.5f, 0xeeee00, "��: %d", piece.b);
	DxLib::ScreenFlip();

	return std::move(own);
}