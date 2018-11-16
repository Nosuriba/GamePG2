#pragma once
#include "PlayerType.h"
class TypeMan :
	public PlayerType
{
public:
	TypeMan();
	~TypeMan();
	PL_TYPE GetType(void);
	void Update(mouse_int mButton, Vector2 pos);
};

