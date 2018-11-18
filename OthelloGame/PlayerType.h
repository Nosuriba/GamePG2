#pragma once
#include "MouseCtl.h"

class GameBoard;

class PlayerType
{
public:
	virtual ~PlayerType();
	virtual PL_TYPE GetType(void) = 0;
	virtual void Update(int& data, Vector2& pos, std::weak_ptr<GameBoard> boardPtr) = 0;
};

