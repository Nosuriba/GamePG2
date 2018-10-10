#pragma once

/* ピースの状態*/
enum PIECE_ST
{
	PIECE_NON,		// 空白
	PIECE_B,		// 黒
	PIECE_W,		// 白
	PIECE_MAX		// ピースの最大数
};


class PieceState
{
public:
	virtual ~PieceState();
	virtual PIECE_ST GetState(void) = 0;
	virtual unsigned int GetDrawColor(void) = 0;
};

