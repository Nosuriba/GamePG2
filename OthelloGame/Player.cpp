#include <DxLib.h>
#include "Player.h"
#include "MouseCtl.h"
#include "GameBoard.h"
#include "GamePiece.h"

int Player::playerCnt = 0;

Player::Player()
{
	/* �e�v���C���[�ɐF�̎w����s���Ă��� */
	playerCnt++;
	id = (PIECE_ST)playerCnt;
}


Player::~Player()
{
}

void Player::Update()
{
	
}

bool Player::ChangePlayer(const MouseCtl & mouse, GameBoard & gBoard)
{
	gBoard.Draw();
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		gBoard.SetPiece(mouse.GetPoint(), id);
		return true;
	}
	return false;
}