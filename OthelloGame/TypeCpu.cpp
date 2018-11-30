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

void TypeCpu::Update(int& data, Vector2& pos, std::weak_ptr<GameBoard> boardPtr)
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

	pointList = boardPtr.lock()->GetPieceTbl();

	// CPUのピースをランダムで配置している
	if (pointList.size() > 0)
	{
		auto itr = pointList.begin();
		auto rand = GetRand(pointList.size() - 1);

		for (int i = 0; i < rand; i++)
		{
			itr++;
		}
		pos = boardPtr.lock()->ChangeTblToScr((*itr));
	}
	else
	{
		pos = { 0,0 };
	}
	
}
