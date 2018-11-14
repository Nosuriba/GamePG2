#include <DxLib.h>
#include "Player.h"
#include "MouseCtl.h"
#include "GameBoard.h"
#include "GamePiece.h"
#include "PieceTray.h"

PIECE_ST Player::id = PIECE_ST::PIECE_NON;

Player::Player(Vector2 boardSize, PL_TYPE type)
{
}

Player::~Player()
{
	id = PIECE_ST::PIECE_NON;
}

bool Player::Draw(void)
{
	// pTray‚Ì’†g‚ª“ü‚Á‚Ä‚¢‚ê‚Î•`‰æ‚ğs‚¤ 
	if (pTray)
	{
		(*pTray).Draw();
		return true;
	}
	return false;
}

PL_TYPE Player::pGetType(void)
{
	return pType;
}

bool Player::SetTurn(bool flag)
{
	return (*pTray).SetTurnFlag(flag);
}
