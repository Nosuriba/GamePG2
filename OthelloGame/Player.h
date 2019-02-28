#pragma once
#include "GamePiece.h"
#include "SceneState.h"

class PieceTray;
class MouseCtl;
class GameBoard;

class Player
{
public:
	Player(Vector2 boardSize);
	~Player();
	bool Draw();
	PIECE_ST pGetID();
	bool TurnAct(mouse_array mouse, GameBoard& gBoard);
	bool SetTurn(bool flag);
	void ReleaseTray(PIECE_ST id);
private:
	static int playerCnt;
	Vector2 boardSize = { 0,0 };
	PIECE_ST id;
	std::unique_ptr<PieceTray> pTray;
};

