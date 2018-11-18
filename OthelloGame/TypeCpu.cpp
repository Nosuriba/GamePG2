#include <DxLib.h>
#include "PieceSt.h"
#include "TypeCpu.h"
#include "GameBoard.h"



TypeCpu::TypeCpu()
{
}


TypeCpu::~TypeCpu()
{
}

PL_TYPE TypeCpu::GetType(void)
{
	return PL_TYPE::CPU;
}

void TypeCpu::Update(int& data, Vector2& pos, std::weak_ptr<GameBoard> boardPtr)
{
	if (data == 0)
	{
		data = MOUSE_INPUT_LEFT;
	}
	else
	{
		data = 0;
	}
	boardPtr.lock()->CheckPutPieceFlag(static_cast<PIECE_ST>(GetType()));
	pos = boardPtr.lock()->PutPieceCpu();
}
