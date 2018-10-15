#pragma once
#include "PieceState.h"
class PieceChar3 :
	public PieceState
{
public:
	PieceChar3();
	~PieceChar3();
	PIECE_ST GetState(void);
	unsigned int GetDrawColor(void);
};

