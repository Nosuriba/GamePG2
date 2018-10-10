#include "PieceWhite.h"



PieceWhite::PieceWhite()
{
}


PieceWhite::~PieceWhite()
{
}

PIECE_ST PieceWhite::GetState(void)
{
	return PIECE_W;
}

unsigned int PieceWhite::GetDrawColor(void)
{
	return 0xffffff;
}