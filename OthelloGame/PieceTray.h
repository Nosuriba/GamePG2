#pragma once
#include "GamePiece.h"

class PieceTray
{
public:
	PieceTray();
	PieceTray(PIECE_ST pState);
	~PieceTray();

	bool Draw(void);
private:
	bool AddPiece(void);
	piece_list pieceList;

	PIECE_ST pState;
	Vector2  pos;
	Vector2  pCnt;

};

