#pragma once
#include "PieceState.h"
class PieceChar2 :
	public PieceState
{
public:
	PieceChar2();
	~PieceChar2();
	PIECE_ST GetState(void);
	unsigned int GetDrawColor(void);
};

