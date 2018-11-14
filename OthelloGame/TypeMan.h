#pragma once
#include "Player.h"

class TypeMan :
	public Player
{
public:
	TypeMan(Vector2 boardSize, PL_TYPE type);
	~TypeMan();
	PIECE_ST pGetID(void);
	bool TurnAct(const MouseCtl& mouse, GameBoard& gBoard);
public:
	PIECE_ST id;
};

