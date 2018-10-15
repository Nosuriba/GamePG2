#pragma once
#include "PieceState.h"
class PieceChar4 :
	public PieceState
{
public:
	PieceChar4();
	~PieceChar4();
	PIECE_ST GetState(void);
	virtual unsigned int GetDrawColor(void);
};

