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
	oldState		 = pState;
	reverseCnt		 = 0;
	SetState(pState, 0);
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

void GamePiece::SetState(PIECE_ST pState, int reserveCnt)
{
	this->reverseCnt = reserveCnt;

	/* リストの中身が空でない時、先頭の要素を削除している */
	if (this->pState.size() > 0)
	{
		oldState = (**GamePiece::pState.begin()).GetState();
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

void GamePiece::ResetAnim(int reverseCnt)
{
	this->reverseCnt = reverseCnt;
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
	/* アニメーション用の変数 */
	int invCnt = (reverseCnt / 20);
	int animCnt = (reverseCnt / 2) % 10;
	double drawSize = (1.0 - (animCnt * 0.1)) - invCnt;

	if (drawSize < 0.0)
	{
		drawSize = 0.0;
	}

	state = (reverseCnt < 0
		  ?  state = (**pState.begin()).GetState()
		  :  state = oldState);

	/* ピースの状態によって、描画するピースの色を設定している */
	if (state == PIECE_W)
	{
		DxLib::DrawRotaGraph(pos.x + drawOffset.x + (PIECE_SIZE / 2), pos.y + drawOffset.y + (PIECE_SIZE / 2), drawSize, 0.0, 
							 LpImageMng.ImgGetID("image/piece/player1.png")[0], true);
		/*DxLib::DrawGraph(pos.x, pos.y, LpImageMng.ImgGetID("image/piece/charPiece1.png")[0], true);*/
	}
	else if (state == PIECE_B)
	{
		DxLib::DrawRotaGraph(pos.x + drawOffset.x + (PIECE_SIZE / 2), pos.y + drawOffset.y + (PIECE_SIZE / 2), drawSize, 0.0, 
							 LpImageMng.ImgGetID("image/piece/player2.png")[0], true);
	}
	else
	{
	}
}

int DrawBox(const Vector2& sPos, const Vector2& ePos, unsigned int color, int fillFlag)
{
	DxLib::DrawBox(sPos.x, sPos.y, ePos.x, ePos.y, color, fillFlag);
	return 0;
}