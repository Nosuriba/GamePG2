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
	/* �{�^���������O�ɁA���݉������{�^���̏���
	�Â��{�^���̏��ɓn���Ă��� */
	mButton[PUSH_OLD] = mButton[PUSH_NOW];
	mButton[PUSH_NOW] = DxLib::GetMouseInput();

	/* �{�^�����������ʒu�̍��W���擾���Ă��� */
	DxLib::GetMousePoint(&pos.x, &pos.y);
}
