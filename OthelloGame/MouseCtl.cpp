#include <DxLib.h>
#include "MouseCtl.h"
#include "Vector2.h"
#include "TypeMan.h"
#include "TypeCpu.h"

MouseCtl::MouseCtl()
{
	pos = { 0,0 };
}

MouseCtl::MouseCtl(PL_TYPE type)
{
	
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

PL_TYPE MouseCtl::GetPlType(void)
{
	return (*plType).GetType();
}

void MouseCtl::SetPlType(PL_TYPE type)
{
	if (type == PL_TYPE::MAN)
	{
		plType = std::make_unique<TypeMan>();
	}
	else if (type == PL_TYPE::CPU)
	{
		plType = std::make_unique<TypeCpu>();
	}
}

void MouseCtl::Update()
{
	// プレイヤーのターンの時にマウスのクリックを更新する
	if ((*plType).GetType() == PL_TYPE::MAN)
	{
		mButton[PUSH_OLD] = mButton[PUSH_NOW];
		mButton[PUSH_NOW] = DxLib::GetMouseInput();
		//(*plType).Update(mButton, pos);
	}
	else
	{
		mButton[PUSH_NOW] = 0;
		pos = { 0,0 };
	}
	
	// ボタンを押した位置の座標を取得している 
	//DxLib::GetMousePoint(&pos.x, &pos.y);
}
