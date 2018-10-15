#pragma once
#include "GamePiece.h"

class PieceTray;
class MouseCtl;
class GameBoard;

class Player
{
public:
	Player();
	~Player();
	void Update();
	bool Draw(void);
	PIECE_ST pGetID(void);
	bool TurnAct(const MouseCtl& mouse, GameBoard& gBoard);
private:
	PIECE_ST id;
	static int playerCnt;
	std::unique_ptr<PieceTray> pTray;
};

