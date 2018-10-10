#include <DxLib.h>
#include "GamePiece.h"
#include "ImageMng.h"
#include "PieceWhite.h"
#include "PieceBlack.h"

GamePiece::GamePiece()
{
}

GamePiece::GamePiece(Vector2 vec)
{
	this->pos	 = vec;
}


GamePiece::~GamePiece()
{
}

PIECE_ST GamePiece::GetState(void)
{
	if (*(pState.begin()))
	{
		return (**pState.begin()).GetState();
	}

	return PIECE_NON;
}

void GamePiece::SetState(PIECE_ST pState)
{
	if (pState == PIECE_W)
	{
		this->pState.push_front(std::make_unique<PieceWhite>());
	}
	else
	{
		this->pState.push_front(std::make_unique<PieceBlack>());
	}
}

void GamePiece::Draw(void)
{
	unsigned int color = 0xff0000;

	/* ピースの状態によって、ピースの画像を描画している */
	if ((*pState.begin())->GetState() == PIECE_W)
	{
		DxLib::DrawGraph(pos.x, pos.y, LpImageMng.ImgGetID("image/player1.png")[0], true);
		//DxLib::DrawCircle(pos.x + offset.x, pos.y + offset.y, 25, 0xffffff, true);
	}
	else if ((*pState.begin())->GetState() == PIECE_B)
	{
		DxLib::DrawGraph(pos.x, pos.y, LpImageMng.ImgGetID("image/player2.png")[0], true);
	}
	else
	{
	}
}


/*color = (*pState).GetDrawColor();
if (pState)
{
Dxlib::drawcircle(pos.x, pos.y, 25, color, true);
}
else
{
Dxlib::drawcircle(pos.x, pos.y, 25, color, true);
}
*/