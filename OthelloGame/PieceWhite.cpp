#include "PieceWhite.h"



PieceWhite::PieceWhite()
{
}


PieceWhite::~PieceWhite()
{
}

PIECE_ST PieceWhite::GetState(void)
{
	return PIECE_ST::W;
}

std::string PieceWhite::GetDrawImage(void)
{
	return "image/piece/player1.png";
}