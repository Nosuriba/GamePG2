#include <DxLib.h>
#include "Player.h"
#include "MouseCtl.h"
#include "GameBoard.h"
#include "GamePiece.h"
#include "PieceTray.h"

int Player::playerCnt = 0;

Player::Player(Vector2 boardSize)
{
	// �e�v���C���[�ɐF�̎w����s���Ă��� 
	playerCnt++;
	id = (PIECE_ST)playerCnt;
	pTray = std::make_unique<PieceTray>(id, boardSize);
}

Player::~Player()
{
	playerCnt = 0;
}

void Player::Update()
{
}

bool Player::Draw(void)
{
	// pTray�̒��g�������Ă���Ε`����s�� 
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

bool Player::TurnAct(const MouseCtl& mouse, GameBoard& gBoard)
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

bool Player::SetTurn(bool flag)
{
	return (*pTray).SetTurnFlag(flag);
}
