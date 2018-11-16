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
	bool Draw(void);
	PIECE_ST pGetID(void);
	bool TurnAct(std::array<std::shared_ptr<MouseCtl>, static_cast<int>(PIECE_ST::MAX)> mouse, GameBoard& gBoard);
	bool SetTurn(bool flag);
private:
	static int playerCnt;
	Vector2 boardSize = { 0,0 };
	PIECE_ST id;
	std::unique_ptr<PieceTray> pTray;
};

