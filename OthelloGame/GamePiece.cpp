#include "GamePiece.h"
#include "ImageMng.h"
#include "PieceWhite.h"
#include "PieceBlack.h"
#include "PieceChar1.h"
#include "PieceChar2.h"
#include "PieceChar3.h"
#include "PieceChar4.h"

GamePiece::GamePiece(const Vector2& pos, const Vector2& drawOffset, PIECE_ST pState)
{
	this->pos		 = pos;
	this->drawOffset = drawOffset;
	SetState(pState);
}


GamePiece::~GamePiece()
{
}

PIECE_ST GamePiece::GetState(void)
{
	/* 先頭の要素に入っているピースの状態を返している */
	if (*(pState.begin()))
	{
		return (**pState.begin()).GetState();
	}

	return PIECE_NON;
}

void GamePiece::SetState(PIECE_ST pState)
{
	/* リストの中身が空でない時、先頭の要素を削除している */
	if (this->pState.size() > 0)
	{
		this->pState.pop_front();
	}

	/* 引数で渡された情報を使用して、リストの先頭に
	　 インスタンスを行っている */
	if (pState == PIECE_W)
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

void GamePiece::Draw(void)
{
	unsigned int color = 0xff0000;
	
	/* ピースの状態によって、描画するピースを設定している */
	if ((**pState.begin()).GetState() == PIECE_W)
	{
		DxLib::DrawGraph(pos.x + drawOffset.x, pos.y + drawOffset.y, LpImageMng.ImgGetID("image/piece/player1.png")[0], true);
		/*DxLib::DrawGraph(pos.x, pos.y, LpImageMng.ImgGetID("image/piece/charPiece1.png")[0], true);*/
	}
	else if ((**pState.begin()).GetState() == PIECE_B)
	{
		DxLib::DrawGraph(pos.x + drawOffset.x, pos.y + drawOffset.y, LpImageMng.ImgGetID("image/piece/player2.png")[0], true);
	}
	else
	{
	}
}

int DrawBox(Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag)
{
	DxLib::DrawBox(sPos.x, sPos.y, ePos.x, ePos.y, color, fillFlag);
	return 0;
}