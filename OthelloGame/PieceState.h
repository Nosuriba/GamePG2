#pragma once
#include "PieceST.h"

struct PieceState
{
	virtual ~PieceState();
	virtual PIECE_ST GetState(void) = 0;
	virtual std::string GetDrawImage(void) = 0;
};

