#include "Player.h"

#define PLAYER_MAX (4)

int Player::playerID;

Player::Player()
{
	playerID = 0;
}


Player::~Player()
{
}

bool Player::pieceFlag(bool pFlag)
{
	return pFlag;
}

int Player::playerNum()
{
	return playerID;
}

void Player::registNum(void)
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
