#include "TypeCpu.h"
#include "GameBoard.h"
#include "MouseCtl.h"
#include "PieceTray.h"

TypeCpu::TypeCpu(Vector2 boardSize, PL_TYPE type) : Player(boardSize, type)
{
	TypeCpu::id = ++(Player::id);
	pType = type;
	pTray = std::make_unique<PieceTray>(id, boardSize);
}

TypeCpu::~TypeCpu()
{
}

PIECE_ST TypeCpu::pGetID(void)
{
	return TypeCpu::id;
}

bool TypeCpu::TurnAct(const MouseCtl & mouse, GameBoard & gBoard)
{
	if (gBoard.CheckPutPieceFlag(id))
	{
		if (gBoard.CheckReverse(gBoard.PutPieceCpu(), id))
		{
			gBoard.SetPiece(gBoard.PutPieceCpu(), id);
			return true;
		}
	}
	return false;
}
