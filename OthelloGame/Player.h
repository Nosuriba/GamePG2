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
	bool pieceFlag(bool pFlag);
	void registNum(void);
	int playerNum();
	// PL_NUM playerNum();
private:
	/*プレイヤーの順番を登録するかの判定用*/
	
	int  player;
	std::deque<int> pNum;

	// PL_NUM player;
	// std::deque<PL_NUM> pNum;
};

