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

void TypeMan::Update(mouse_int mButton, Vector2 pos)
{
	mButton[PUSH_NOW] = DxLib::GetMouseInput();
	DxLib::GetMousePoint(&pos.x, &pos.y);
}
