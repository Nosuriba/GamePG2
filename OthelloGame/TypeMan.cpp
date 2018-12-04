#include <DxLib.h>
#include "TypeMan.h"

TypeMan::TypeMan()
{
}

TypeMan::~TypeMan()
{
}

PL_TYPE TypeMan::GetType(void)
{
	return PL_TYPE::MAN;
}

void TypeMan::Update(int& data, Vector2& pos, std::weak_ptr<GameBoard> boardPtr, PIECE_ST pState)
{
	data = DxLib::GetMouseInput();
	DxLib::GetMousePoint(&pos.x, &pos.y);
}
