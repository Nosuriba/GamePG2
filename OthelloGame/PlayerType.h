#pragma once
#include "MouseCtl.h"

class PlayerType
{
public:
	virtual ~PlayerType();
	virtual PL_TYPE GetType(void) = 0;
	virtual void Update(mouse_int mButton, Vector2 pos) = 0;
};

