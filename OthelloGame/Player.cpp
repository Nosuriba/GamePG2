#include "Player.h"

#define PLAYER_MAX (4)

Player::Player()
{
	player = 0;
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
	return player;
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
	player = pNum.front();
	pNum.pop_front();
	pNum.push_back(player);
}

//PL_NUM Player::playerNum()
//{
//	return player;
//}
