#pragma once
#include "PieceState.h"
class PieceChar1 :
	public PieceState
{
public:
	PieceChar1();
	~PieceChar1();
	PIECE_ST GetState(void);
	unsigned int GetDrawColor(void);
};

