#pragma once
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"
#include "PieceState.h"

using pState_ptr = std::unique_ptr<PieceState>;
using pState_list = std::list<pState_ptr>;

class GamePiece
{
public:
	GamePiece();
	GamePiece(Vector2 vec);
	~GamePiece();
	PIECE_ST GetState(void);
	void SetState(PIECE_ST pState);
	void Draw(void);
private:
	pState_list  pState;
	Vector2 pos;
};

