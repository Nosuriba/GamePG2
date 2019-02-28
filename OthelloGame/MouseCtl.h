#pragma once
#include <array>
#include <thread>
#include <mutex>
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

typedef struct
{
	Vector2 pos;
	int mouseID;
}mouse_data;


// ƒ}ƒEƒX‚Ìî•ñ‚ğŒÅ’è’·”z—ñ‚ÅŠi”[‚·‚é‚½‚ß‚ÌŒ^ 
using mouse_int = std::array<int, PUSH_MAX>;

class MouseCtl
{
public:
	MouseCtl();
	~MouseCtl();
	Vector2 GetPoint() const;
	mouse_int GetButton() const;
	PL_TYPE GetPlType();
	void SetPlType(PL_TYPE type);
	void ThreadStop();
	void Update();
	void Update(std::shared_ptr<GameBoard> boardPtr, PIECE_ST pState);
private:
	mouse_data data;
	std::unique_ptr<PlayerType> plType;
	std::thread threadAI;
	mouse_int mButton;
	const int limTime;

};

