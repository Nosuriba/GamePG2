#pragma once
#include "PlayerType.h"
class TypeCpu :
	public PlayerType
{
public:
	TypeCpu();
	~TypeCpu();
	PL_TYPE GetType(void);
	void Update(int& data, Vector2& pos, std::weak_ptr<GameBoard> boardPtr);
};

