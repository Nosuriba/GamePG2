#pragma once
#include "GamePiece.h"

class PieceTray;
class MouseCtl;
class GameBoard;

class Player
{
public:
	Player(Vector2 boardSize);
	~Player();
	void Update();
	bool Draw(void);
	PIECE_ST pGetID(void);
	bool TurnAct(const MouseCtl& mouse, GameBoard& gBoard);
	bool SetTurn(bool flag);
private:
	Vector2 boardSize = { 0,0 };
	PIECE_ST id;
	static int playerCnt;
	std::unique_ptr<PieceTray> pTray;
};

