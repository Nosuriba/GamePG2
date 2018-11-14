#include "TypeMan.h"
#include "GameBoard.h"
#include "MouseCtl.h"
#include "PieceTray.h"


TypeMan::TypeMan(Vector2 boardSize, PL_TYPE type) : Player(boardSize, type)
{
	TypeMan::id = ++(Player::id);
	pType = type;
	pTray = std::make_unique<PieceTray>(id, boardSize);
}

TypeMan::~TypeMan()
{
}

PIECE_ST TypeMan::pGetID(void)
{
	return TypeMan::id;
}

bool TypeMan::TurnAct(const MouseCtl & mouse, GameBoard & gBoard)
{
	(*pTray).SetTurnFlag(true);
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		if (gBoard.CheckReverse(mouse.GetPoint(), id))
		{
			gBoard.SetPiece(mouse.GetPoint(), id);
			return true;
		}
	}
	return false;
}
