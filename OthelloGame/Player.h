#pragma once
#include "GamePiece.h"

class MouseCtl;
class GameBoard;

class Player
{
public:
	Player();
	~Player();
	void Update();	
	bool ChangePlayer(const MouseCtl& mouse, GameBoard& gBoard);
private:
	PIECE_ST id;
	static int playerCnt;
};

