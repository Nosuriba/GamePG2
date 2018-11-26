#include <cmath>
#include "ImageMng.h"
#include "GamePiece.h"
#include "PieceST.h"
#include "PieceWhite.h"
#include "PieceBlack.h"

// ���]�A�j���[�V�����p�̃J�E���g(�������C�����Ȃ���..)
#define REVERSE_ANIM_CNT   (20)
#define ANIM_FLAME_CNT	   (10)
#define ANIM_FLAME_INV_CNT (REVERSE_ANIM_CNT / ANIM_FLAME_CNT)
#define ANIM_FLOAT_CNT	   (ANIM_FLAME_INV_CNT * 2)

GamePiece::GamePiece(const Vector2& pos, const Vector2& drawOffset, PIECE_ST pState)
{
	this->pos		 = pos;
	this->drawOffset = drawOffset;
	drawSize		 = 0;
	oldState		 = pState;
	reverseCnt		 = 0;
	SetState(pState, 0);
}

GamePiece::~GamePiece()
{
}

PIECE_ST GamePiece::GetState(void)
{
	 // �擪�̗v�f�ɓ����Ă���s�[�X�̏�Ԃ�Ԃ��Ă��� 
	if (*(pState.begin()))
	{
		return (**pState.begin()).GetState();
	}

	return PIECE_ST::NON;
}

void GamePiece::SetState(PIECE_ST pState, int reserveCnt)
{
	this->reverseCnt = reserveCnt;

	// ���X�g�̒��g����łȂ����A�擪�̗v�f���폜���Ă���
	if (this->pState.size() > 0)
	{
		oldState = (**GamePiece::pState.begin()).GetState();
		this->pState.pop_front();
	}
	
	if (pState == PIECE_ST::W)
	{
		this->pState.push_front(std::make_unique<PieceWhite>());
	}
	else
	{
		this->pState.push_front(std::make_unique<PieceBlack>());
	}
}

#define PIECE_SIZE 64		
int GamePiece::GetSize(void)
{
	return PIECE_SIZE;
}

bool GamePiece::SetPos(const Vector2 & pos)
{
	this->pos = pos;
	return true;
}

bool GamePiece::SetDrawOffset(const Vector2 & drawOffset)
{
	this->drawOffset = drawOffset;
	return true;
}

void GamePiece::Update(void)
{
	if (reverseCnt < 0)
	{
		return;
	}
	reverseCnt--;
}

void GamePiece::Draw(void)
{
	// �A�j���[�V�����p�̕ϐ� 
	double debugSize = 0;
	PIECE_ST state  = oldState;

	// ���]�A�j���[�V�����̐ݒ�
	if (reverseCnt < REVERSE_ANIM_CNT)
	{
		int animCnt = (reverseCnt / ANIM_FLAME_INV_CNT) % ANIM_FLAME_CNT;
		drawSize = -1.0 + (animCnt * 0.2);
		
		state = (drawSize > 0 ? state = oldState : state = (**pState.begin()).GetState());
	}
	
	// �s�[�X�̔��]���ɕ������邽�߂̃A�j���[�V�����ݒ�
	debugSize = (int)(((drawSize * ANIM_FLAME_CNT) / ANIM_FLOAT_CNT) + 2) % 3;
	debugSize = abs(debugSize * 0.1);

	 // �s�[�X�̏�Ԃɂ���āA�`�悷��s�[�X�̐F��ݒ肵�Ă��� 
	if (state == PIECE_ST::W)
	{
		DxLib::DrawRotaGraph3(pos.x + drawOffset.x + (PIECE_SIZE / 2), pos.y + drawOffset.y + (PIECE_SIZE / 2),
							 (PIECE_SIZE / 2), (PIECE_SIZE / 2),
							  abs(drawSize) + debugSize, 1.0 + debugSize, 0.0,
							  LpImageMng.ImgGetID("image/piece/player1.png")[0], true);
	}
	else if (state == PIECE_ST::B)
	{
		DxLib::DrawRotaGraph3(pos.x + drawOffset.x + (PIECE_SIZE / 2), pos.y + drawOffset.y + (PIECE_SIZE / 2),
							 (PIECE_SIZE / 2), (PIECE_SIZE / 2),
							  abs(drawSize) + debugSize, 1.0 + debugSize, 0.0,
							  LpImageMng.ImgGetID("image/piece/player2.png")[0], true);
	}
	else{}
}

int DrawBox(const Vector2& sPos, const Vector2& ePos, unsigned int color, int fillFlag)
{
	DxLib::DrawBox(sPos.x, sPos.y, ePos.x, ePos.y, color, fillFlag);
	return 0;
}