#include <DxLib.h>
#include "Player.h"
#include "MouseCtl.h"
#include "GameBoard.h"
#include "GamePiece.h"
#include "PieceTray.h"

int Player::playerCnt = 0;

Player::Player(Vector2 boardSize)
{
	id = (PIECE_ST)playerCnt;
	playerCnt++;
	pTray = std::make_unique<PieceTray>(id, boardSize);
}

Player::~Player()
{
	playerCnt = 0;
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

PIECE_ST Player::pGetID(void)
{
	return id;
}

bool Player::TurnAct(std::array<std::shared_ptr<MouseCtl>, static_cast<int>(PIECE_ST::MAX)> mouse, GameBoard & gBoard)
{
	(*pTray).SetTurnFlag(true);
	if (gBoard.CheckReverse((*mouse[static_cast<int>(id)]).GetPoint(), id))
	{
		gBoard.SetPiece((*mouse[static_cast<int>(id)]).GetPoint(), id);
		return true;
	}
	return false;
}

bool Player::SetTurn(bool flag)
{
	return (*pTray).SetTurnFlag(flag);
}
