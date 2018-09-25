#include <DxLib.h>
#include "Player.h"
#include "MouseCtl.h"

#define PLAYER_MAX (4)

int Player::playerID;

Player::Player()
{
	playerID = 0;
}


Player::~Player()
{
}

void Player::Update()
{
	
}

bool Player::PieceFlag(const MouseCtl & mouseCtl)
{
	if (mouseCtl.GetButton()[PUSH_NOW] & (~mouseCtl.GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		return true;
	}
	return false;
}

int Player::PlayerNum()
{
	return playerID;
}

void Player::RegistNum(void)
{
	if (pNum.size() == 0)
	{
		/* �v���C���[�̏��Ԃ����X�g�ɓo�^���Ă���B*/
		for (int pl = 1; pl <= PLAYER_MAX; pl++)
		{
			pNum.push_back(pl);
		}
	}
	/*�v���C���[�̏��Ԃ����ւ��鏈��*/
	playerID = pNum.front();
	pNum.pop_front();
	pNum.push_back(playerID);
}

//PL_NUM Player::playerNum()
//{
//	return player;
//}
