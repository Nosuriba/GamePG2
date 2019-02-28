#pragma once
#include "PieceST.h"

struct PieceState
{
	virtual ~PieceState();
	virtual PIECE_ST GetState()		   = 0;
	virtual std::string GetDrawImage() = 0;
};

