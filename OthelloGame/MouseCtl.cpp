#include <DxLib.h>
#include "MouseCtl.h"
#include "Vector2.h"

MouseCtl::MouseCtl()
{
	pos = { 0,0 };
}


MouseCtl::~MouseCtl()
{
}

Vector2 MouseCtl::GetPoint(void) const
{
	return pos;
}

mouse_int MouseCtl::GetButton(void) const
{
	return mButton;
}

void MouseCtl::Update(void)
{
	/* クリックをする前に、押したクリックの情報を
	   古いクリックの情報に渡している */
	mButton[PUSH_OLD] = mButton[PUSH_NOW];
	mButton[PUSH_NOW] = DxLib::GetMouseInput();

	// ボタンを押した位置の座標を取得している 
	DxLib::GetMousePoint(&pos.x, &pos.y);
}
