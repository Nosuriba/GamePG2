#pragma once
#include "GamePiece.h"

class PieceTray
{
public:
	PieceTray();
	PieceTray(PIECE_ST pState, Vector2 boardSize);
	~PieceTray();
	bool Draw(void);
	bool SetTurnFlag(bool flag);
private:
	bool AddPiece(void);
	piece_list pieceList;

	PIECE_ST pState;
	Vector2  pos;
	Vector2  pCnt;
	bool	 turnFlag;
};

