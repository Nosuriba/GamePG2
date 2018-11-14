#pragma once
#include "Player.h"

class TypeCpu :
	public Player
{
public:
	TypeCpu(Vector2 boardSize, PL_TYPE type);
	~TypeCpu();
	PIECE_ST pGetID(void);
	bool TurnAct(const MouseCtl& mouse, GameBoard& gBoard);
private:
	PIECE_ST id;
};

