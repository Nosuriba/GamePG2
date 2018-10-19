#pragma once
#include "GamePiece.h"

class PieceTray
{
public:
	PieceTray(PIECE_ST pState, Vector2 boardSize);
	~PieceTray();
	/* ターン処理を行っているプレイヤーの情報を取得している */
	bool SetTurnFlag(bool flag);
	bool Draw(void);
private:
	bool AddPiece(void);
	
	piece_list pieceList;
	PIECE_ST pState = PIECE_NON;

	Vector2  pos;
	
	bool	 turnFlag;
};

