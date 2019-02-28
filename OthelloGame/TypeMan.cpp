#include <DxLib.h>
#include "TypeMan.h"

TypeMan::TypeMan()
{
	isEnd	 = false;
	isTimeUp = false;
}

TypeMan::~TypeMan()
{
}

PL_TYPE TypeMan::GetType()
{
	return PL_TYPE::MAN;
}

bool TypeMan::GetIsEnd()
{
	return isEnd;
}

bool TypeMan::GetIsTimeUp()
{
	return isTimeUp;
}

mouse_data TypeMan::GetMouseData()
{
	return data;
}

void TypeMan::Update(std::weak_ptr<GameBoard> boardPtr, PIECE_ST pState)
{
	std::lock_guard<std::mutex> lock(mtx);
	isEnd		 = false;
	data.mouseID = DxLib::GetMouseInput();

	if (LpGameScene.GetMilliTime() == 0) { LpGameScene.StartTime();}

	if (isTimeUp)
	{
		isEnd = true;
		data.pos = boardPtr.lock()->GetRandomPos();
		data.mouseID = MOUSE_INPUT_LEFT;
		return;
	}
	
	if (data.mouseID & MOUSE_INPUT_LEFT)
	{
		_RPT0(_CRT_WARN, "MAN : GetPos\n");
		isEnd = true;
		DxLib::GetMousePoint(&data.pos.x, &data.pos.y);
		return;
	}
}
