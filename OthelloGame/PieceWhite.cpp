#include "PieceWhite.h"



PieceWhite::PieceWhite()
{
}


PieceWhite::~PieceWhite()
{
}

PIECE_ST PieceWhite::GetState()
{
	return PIECE_ST::W;
}

std::string PieceWhite::GetDrawImage()
{
	return "resource/image/player1.png";
}