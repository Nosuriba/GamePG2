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
	bool Draw(void);
	PL_TYPE pGetType(void);

	// �N���X�̌p�����ł��ꂼ��ݒ��ύX���Ă���
	virtual PIECE_ST pGetID(void) = 0;
	virtual bool TurnAct(const MouseCtl& mouse, GameBoard& gBoard) = 0;
	bool SetTurn(bool flag);
protected:
	Vector2 boardSize = { 0,0 };
	static PIECE_ST id;
	PL_TYPE pType;
	std::unique_ptr<PieceTray> pTray;
private:
};

