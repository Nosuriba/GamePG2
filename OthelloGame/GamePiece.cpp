#include <DxLib.h>
#include "GamePiece.h"

GamePiece::GamePiece()
{
	 //pState = PIECE_NON;
}

GamePiece::GamePiece(Vector2 vec, Vector2 offset)
{
	pState		 = PIECE_NON;
	this->pos	 = vec;
	this->offset = offset;
}


GamePiece::~GamePiece()
{
}

PIECE_ST GamePiece::GetState(void)
{
	return pState;
}

void GamePiece::SetState(PIECE_ST pState)
{
	this->pState = pState;
}

void GamePiece::SetReverse(void)
{
	/* ����4�l�v���C�p��4��ނ̃s�[�X���쐬���Ă��邪�A
	�@ �v���C���[�̃��[�v���ł��Ă��邩�̊m�F���ł�����
	   2�l�v���C�p�ɒ����Ă���*/
	if (pState != PIECE_NON)
	{
		if (pState == PIECE_W | pState == PIECE_C)
		{
			/* �s�[�X�̏�Ԃ𔽓]�����鏈�� */
			pState = (pState == PIECE_W ? pState = PIECE_C : pState = PIECE_W);
		}
		else
		{
			pState = (pState == PIECE_R ? pState = PIECE_B : pState = PIECE_R);
		}
		
	}
	
}

void GamePiece::Draw(void)
{
	/* �s�[�X�̏�Ԃɂ���āA�~�̐F��ς��Ă��� */
	if (pState == PIECE_W)
	{
		DxLib::DrawCircle(pos.x + offset.x, pos.y + offset.y, 25, 0xffffff, true);
	}
	else if (pState == PIECE_C)
	{
		DxLib::DrawCircle(pos.x + offset.x, pos.y + offset.y, 25, 0x000000, true);
	}
	else if (pState == PIECE_R)
	{
		DxLib::DrawCircle(pos.x + offset.x, pos.y + offset.y, 25, 0xff0000, true);
	}
	else if (pState == PIECE_B)
	{
		DxLib::DrawCircle(pos.x + offset.x, pos.y + offset.y, 25, 0x0000ff, true);
	}
	else
	{
	}
}
