#pragma once
#include "PieceState.h"

class PieceBlack :
	public PieceState
{
public:
	PieceBlack();
	~PieceBlack();
	PIECE_ST GetState(void);
	std::string GetDrawImage(void);
};

