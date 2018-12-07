#include <cmath>
#include "ImageMng.h"
#include "GamePiece.h"
#include "PieceST.h"
#include "PieceWhite.h"
#include "PieceBlack.h"

GamePiece::GamePiece(const Vector2& pos, const Vector2& drawOffset, PIECE_ST pState) :
drawPieceSize(64),
animCnt(20),
flameCnt(10),
flameInvCnt(animCnt / flameCnt),
holdAnimCnt(flameInvCnt * 2)
{
	this->pos		 = pos;
	this->drawOffset = drawOffset;
	drawSize		 = 0;
	reverseCnt		 = 0;
	SetState(pState, 0);
}

GamePiece::~GamePiece()
{
}

PIECE_ST GamePiece::GetState(void)
{
	 // 先頭の要素に入っているピースの状態を返している 
	if (*(pState.begin()))
	{
		return (**pState.begin()).GetState();
	}

	return PIECE_ST::NON;
}

void GamePiece::SetState(PIECE_ST pState, int reserveCnt)
{
	this->reverseCnt = reserveCnt;

	// リストの中身が空でない時、先頭の要素を削除している
	if (this->pState.size() > 0)
	{
		oldImage = (**GamePiece::pState.begin()).GetDrawImage();
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
	
int GamePiece::GetSize(void)
{
	return drawPieceSize;
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
	// アニメーション用の変数 
	double holdSize = 0;
	std::string image = oldImage;

	// 反転アニメーションの設定
	if (reverseCnt < animCnt)
	{
		int animCnt = (reverseCnt / flameInvCnt) % flameCnt;
		drawSize = -1.0 + (animCnt * 0.2);
		
		image = (drawSize > 0 ? image = oldImage : image = (**pState.begin()).GetDrawImage());
	}
	
	// ピースの反転時に浮かせるためのアニメーション設定
	holdSize = (int)(((drawSize * flameCnt) / holdAnimCnt) + 2) % 3;
	holdSize = abs(holdSize * 0.1);

	// ピースの描画
	DxLib::DrawRotaGraph3(pos.x + drawOffset.x + (drawPieceSize / 2), pos.y + drawOffset.y + (drawPieceSize / 2),
						 (drawPieceSize / 2), (drawPieceSize / 2),
						  abs(drawSize) + holdSize, 1.0 + holdSize, 0.0,
						  LpImageMng.ImgGetID(image)[0], true);
}

int DrawBox(const Vector2& sPos, const Vector2& ePos, unsigned int color, int fillFlag)
{
	DxLib::DrawBox(sPos.x, sPos.y, ePos.x, ePos.y, color, fillFlag);
	return 0;
}