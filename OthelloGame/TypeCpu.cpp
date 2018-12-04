#include <DxLib.h>
#include "PieceSt.h"
#include "TypeCpu.h"
#include "GameBoard.h"

TypeCpu::TypeCpu() : putTimer(60)
{
}

TypeCpu::~TypeCpu()
{
}

PL_TYPE TypeCpu::GetType(void)
{
	return PL_TYPE::CPU;
}

void TypeCpu::Update(int& data, Vector2& pos, std::weak_ptr<GameBoard> boardPtr, PIECE_ST pState)
{
	// 敵のピースを置くまでの間隔
	if (++waitTime <putTimer)
	{
		return;
	}
	waitTime = 0;

	if (data == 0)
	{
		data = MOUSE_INPUT_LEFT;
	}
	else
	{
		data = 0;
	}

	pos = boardPtr.lock()->GetPiecePos(pState);
}
