#include "PieceBlack.h"

PieceBlack::PieceBlack()
{
}


PieceBlack::~PieceBlack()
{
}

PIECE_ST PieceBlack::GetState(void)
{
	return PIECE_ST::B;
}

unsigned int PieceBlack::GetDrawColor(void)
{
	return 0x000000;
}
