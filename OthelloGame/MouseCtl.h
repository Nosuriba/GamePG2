#pragma once
#include <array>
#include "Vector2.h"
#include "PL_TYPE.h"
#include "PieceSt.h"

class PlayerType;
class GameBoard;

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
	PL_TYPE GetPlType(void);
	void SetPlType(PL_TYPE type);
	void Update();
	void Update(std::shared_ptr<GameBoard>, PIECE_ST pState);
private:
	Vector2   pos;
	PL_TYPE	  type;
	std::unique_ptr<PlayerType> plType;
	mouse_int mButton;

};

