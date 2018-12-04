#pragma once
#include <list>
#include "PlayerType.h"
struct TypeCpu : PlayerType
{
	TypeCpu();
	~TypeCpu();
	PL_TYPE GetType(void);
	void Update(int& data, Vector2& pos, std::weak_ptr<GameBoard> boardPtr, PIECE_ST pState);
	Vector2 pointList;
private:
	int waitTime = 0;

	const int putTimer;
};

