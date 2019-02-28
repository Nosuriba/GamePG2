#pragma once
#include <list>
#include "PlayerType.h"
struct TypeCpu : PlayerType
{
	TypeCpu();
	~TypeCpu();
	PL_TYPE GetType();
	bool GetIsEnd();
	bool GetIsTimeUp();
	mouse_data  GetMouseData();
	void Update(std::weak_ptr<GameBoard> boardPtr, PIECE_ST pState);
private:
	int waitTime = 0;
	const int putTimer;
	Vector2 pointList;
};

