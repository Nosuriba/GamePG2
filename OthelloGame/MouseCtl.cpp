#include <DxLib.h>
#include "MouseCtl.h"
#include "GameBoard.h"
#include "TypeMan.h"
#include "TypeCpu.h"

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

PL_TYPE MouseCtl::GetPlType(void)
{
	if (!plType)
	{
		return PL_TYPE::SYS;
	}
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
	// システム処理用のマウス設定
	mButton[PUSH_OLD] = mButton[PUSH_NOW];
	mButton[PUSH_NOW] = DxLib::GetMouseInput();
	DxLib::GetMousePoint(&pos.x, &pos.y);
}

void MouseCtl::Update(std::shared_ptr<GameBoard> boardPtr, PIECE_ST pState)
{
	// プレイヤーのターンの時にマウスのクリックを更新する
	if (!((*plType).GetType() == PL_TYPE::SYS))
	{
		mButton[PUSH_OLD] = mButton[PUSH_NOW];
		(*plType).Update(mButton[PUSH_NOW], pos, boardPtr, pState);
	}
	else
	{
		Update();
	}
}
