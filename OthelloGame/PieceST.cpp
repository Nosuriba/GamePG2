#include <type_traits>
#include "PieceST.h"

PIECE_ST begin(PIECE_ST)
{
	return PIECE_ST::PIECE_NON;
}

PIECE_ST end(PIECE_ST)
{
	return PIECE_ST::PIECE_MAX;
}

PIECE_ST operator*(PIECE_ST state)
{
	return state;
}

PIECE_ST operator++(PIECE_ST & state)
{
	return state = PIECE_ST(std::underlying_type<PIECE_ST>::type(state) + 1);
}

PIECE_ST operator--(PIECE_ST & state)
{
	return state = PIECE_ST(std::underlying_type<PIECE_ST>::type(state) - 1);
}
