#pragma once
#include <array>
#include "PlayerType.h"
#include "Vector2.h"

enum M_PUSH
{
	PUSH_NOW,
	PUSH_OLD,
	PUSH_MAX
};


// ƒ}ƒEƒX‚Ìî•ñ‚ğŒÅ’è’·”z—ñ‚ÅŠi”[‚·‚é‚½‚ß‚ÌŒ^ 
using mouse_int = std::array<int, PUSH_MAX>;

class MouseCtl
{
public:
	MouseCtl();
	~MouseCtl();
	Vector2 GetPoint(void) const;
	mouse_int GetButton(void) const;
	void Update(PL_TYPE type);
private:
	Vector2   pos;
	mouse_int mButton;
};

