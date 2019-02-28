#include <DxLib.h>
#include "PieceSt.h"
#include "TypeCpu.h"
#include "GameBoard.h"

TypeCpu::TypeCpu() : putTimer(60)
{
	isEnd	 = false;
	isTimeUp = false;
}

TypeCpu::~TypeCpu()
{
}

PL_TYPE TypeCpu::GetType()
{
	return PL_TYPE::CPU;
}

bool TypeCpu::GetIsEnd()
{
	return isEnd;
}

bool TypeCpu::GetIsTimeUp()
{
	return isTimeUp;
}

mouse_data TypeCpu::GetMouseData()
{
	return data;
}

void TypeCpu::Update(std::weak_ptr<GameBoard> boardPtr, PIECE_ST pState)
{
	std::lock_guard<std::mutex> lock(mtx);
	isEnd = false;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	_RPT0(_CRT_WARN, "CPU : Decide GetPos\n");
	data.mouseID = MOUSE_INPUT_LEFT;
	data.pos = boardPtr.lock()->GetPiecePos(pState);
	
	isEnd = true;
	isTimeUp = true;
	return;
}
