#pragma once

/* ピースの状態(PIECE_NONの位置をPIECE_MAXの位置に変えたやり方もある)*/
enum PIECE_ST
{
	PIECE_NON,
	PIECE_B,		// 黒
	PIECE_W,		// 白
	PIECE_CHAR1,
	PIECE_CHAR2,
	PIECE_CHAR3,
	PIECE_CHAR4,
	PIECE_MAX
};

struct PieceState
{
	virtual ~PieceState();
	virtual PIECE_ST GetState(void) = 0;
	virtual unsigned int GetDrawColor(void) = 0;
};

