#pragma once

#include <deque>

class MouseCtl;

//enum PL_NUM
//{
//	PL_1,
//	PL_2,
//	PL_3,
//	PL_4,
//	PL_MAX
//};

class Player
{
public:
	Player();
	~Player();
	void Update();	
	bool PieceFlag(const MouseCtl& mouseCtl);		// �s�[�X�̐ݒu�����邩�̔���p
	void RegistNum(void);
	int PlayerNum();
	// PL_NUM playerNum();
private:
	/*�v���C���[�̏��Ԃ�o�^���邩�̔���p*/
	
	static int  playerID;
	std::deque<int> pNum;

	// PL_NUM player;
	// std::deque<PL_NUM> pNum;
};

