#include <type_traits>
#include "PL_TYPE.h"

PL_TYPE begin(PL_TYPE)
{
	return PL_TYPE::MAN;
}

PL_TYPE end(PL_TYPE)
{
	return PL_TYPE::MAX;
}

PL_TYPE operator*(PL_TYPE pType)
{
	return pType;
}

PL_TYPE operator++(PL_TYPE pType)
{
	return pType = PL_TYPE(std::underlying_type<PL_TYPE>::type(pType) + 1);
}

PL_TYPE operator--(PL_TYPE pType)
{
	return pType = PL_TYPE(std::underlying_type<PL_TYPE>::type(pType) - 1);
}
