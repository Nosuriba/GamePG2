#pragma once
#include "PieceState.h"

class PieceBlack :
	public PieceState
{
public:
	PieceBlack();
	~PieceBlack();
	PIECE_ST GetState(void);
	unsigned int GetDrawColor(void);
};

