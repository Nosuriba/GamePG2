#pragma once
#include "PlayerType.h"
class TypeCpu :
	public PlayerType
{
public:
	TypeCpu();
	~TypeCpu();
	PL_TYPE GetType(void);
	void Update(mouse_int mButton, Vector2 pos);
};

