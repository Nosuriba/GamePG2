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
	bool PieceFlag(const MouseCtl& mouseCtl);		// ピースの設置をするかの判定用
	void RegistNum(void);
	int PlayerNum();
	// PL_NUM playerNum();
private:
	/*プレイヤーの順番を登録するかの判定用*/
	
	static int  playerID;
	std::deque<int> pNum;

	// PL_NUM player;
	// std::deque<PL_NUM> pNum;
};

