#pragma once
#include "GamePiece.h"
#include "PlayerType.h"

class PieceTray;
class MouseCtl;
class GameBoard;

class Player
{
public:
	Player(Vector2 boardSize, PL_TYPE type);
	~Player();
	void Update();
	bool Draw(void);
	PIECE_ST pGetID(void);
	PL_TYPE pGetType(void);
	bool TurnAct(const MouseCtl& mouse, GameBoard& gBoard, PL_TYPE type);
	bool SetTurn(bool flag);
private:
	Vector2 boardSize = { 0,0 };
	PIECE_ST id;
	PL_TYPE pType;
	static int playerCnt;
	std::unique_ptr<PieceTray> pTray;
};

