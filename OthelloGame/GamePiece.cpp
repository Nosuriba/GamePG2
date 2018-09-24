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
	if (pState != PIECE_NON)
	{
		/* ピースの状態を反転させる処理 */
		pState = (pState == PIECE_W ? pState = PIECE_C : pState = PIECE_W);
	}
	
}

void GamePiece::Draw(void)
{
	/* ピースの状態によって、円の色を変えている */
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
