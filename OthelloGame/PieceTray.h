#pragma once
#include "GamePiece.h"

class PieceTray
{
public:
	PieceTray(PIECE_ST pState, const Vector2& boardSize);
	~PieceTray();
	// ターン処理を行っているプレイヤーの情報を取得している 
	bool SetTurnFlag(bool flag);
	bool ReleasePiece();
	void AddPiece(PIECE_ST id);
	bool Draw();
private:
	bool AddPiece();
	
	piece_sharedList pieceList;
	PIECE_ST pState = PIECE_ST::NON;
	Vector2  pos;
	
	bool	 turnFlag;
};

