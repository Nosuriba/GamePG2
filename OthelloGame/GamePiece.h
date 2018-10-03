#pragma once
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"

/* ピースの状態*/
enum PIECE_ST
{
	PIECE_NON,		// 空白
	PIECE_W,		// 白
	PIECE_B,		// 黒
	PIECE_MAX		// ピースの最大数
};

class GamePiece
{
public:
	GamePiece();
	GamePiece(Vector2 vec);
	~GamePiece();
	PIECE_ST GetState(void);
	void SetState(PIECE_ST pState);
	void SetReverse(void);
	void Draw(void);
private:
	Vector2 pos;
	PIECE_ST pState;
};

