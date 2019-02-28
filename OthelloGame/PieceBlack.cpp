#include "PieceBlack.h"

PieceBlack::PieceBlack()
{
}


PieceBlack::~PieceBlack()
{
}

PIECE_ST PieceBlack::GetState()
{
	return PIECE_ST::B;
}

std::string PieceBlack::GetDrawImage()
{
	return "resource/image/player2.png";
}
