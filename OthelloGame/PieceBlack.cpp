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

std::string PieceBlack::GetDrawImage(void)
{
	return "image/piece/player2.png";
}
