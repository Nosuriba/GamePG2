#pragma once
#include "PlayerType.h"
class TypeMan :
	public PlayerType
{
public:
	TypeMan();
	~TypeMan();
	PL_TYPE GetType(void);
	void Update(int& data, Vector2& pos, std::weak_ptr<GameBoard> boardPtr);
};

