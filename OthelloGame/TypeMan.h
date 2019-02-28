#pragma once
#include "PlayerType.h"

struct TypeMan : PlayerType
{
	TypeMan();
	~TypeMan();
	PL_TYPE GetType();
	bool GetIsEnd();
	bool GetIsTimeUp();
	mouse_data  GetMouseData();
	void Update(std::weak_ptr<GameBoard> boardPtr, PIECE_ST pState);
};

