#include <DxLib.h>
#include "Player.h"
#include "MouseCtl.h"
#include "GameBoard.h"
#include "GamePiece.h"

int Player::playerCnt = 0;

Player::Player()
{
	/* 各プレイヤーに色の指定を行っている */
	playerCnt++;
	id = (PIECE_ST)playerCnt;
}

Player::~Player()
{
}

void Player::Update()
{
	
}

PIECE_ST Player::pGetID(void)
{
	return id;
}

bool Player::TurnAct(const MouseCtl& mouse, GameBoard& gBoard)
{
	bool rtnFlag = false;
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		if (gBoard.SetPiece(mouse.GetPoint(), id))
		{
			rtnFlag = true;
		}
	}
	return rtnFlag;
}