#include <DxLib.h>
#include "Player.h"
#include "MouseCtl.h"
#include "GameBoard.h"
#include "GamePiece.h"
#include "PieceTray.h"

int Player::playerCnt = 0;

Player::Player()
{
	/* 各プレイヤーに色の指定を行っている */
	playerCnt++;
	id = (PIECE_ST)playerCnt;
	pTray = std::make_unique<PieceTray>(id);
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
	/* pTrayの中身が入っていれば描画を行う */
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
	bool rtnFlag = false;
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		if (gBoard.CheckReverse(mouse.GetPoint(), id))
		{
			gBoard.SetPiece(mouse.GetPoint(), id);
			rtnFlag = true;
		}
	}
	return rtnFlag;
}