#include "PlayerType.h"
#include <type_traits>

PL_TYPE begin(PL_TYPE)
{
	return PL_TYPE::PL_MAN;
}

PL_TYPE end(PL_TYPE)
{
	return PL_TYPE::PL_MAX;
}

PL_TYPE operator*(PL_TYPE type)
{
	return type;
}

PL_TYPE operator++(PL_TYPE type)
{
	return type = PL_TYPE(std::underlying_type<PL_TYPE>::type(type) + 1);
}

PL_TYPE operator--(PL_TYPE type)
{
	return type = PL_TYPE(std::underlying_type<PL_TYPE>::type(type) - 1);
}
