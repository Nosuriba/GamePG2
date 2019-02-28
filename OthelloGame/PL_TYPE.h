#pragma once

// ÉvÉåÉCÉÑÅ[ÇÃéÌóﬁ
enum class PL_TYPE
{
	MAN,
	CPU,
	NET,
	SYS,
	MAX
};

PL_TYPE begin(PL_TYPE);
PL_TYPE end(PL_TYPE);
PL_TYPE operator*(PL_TYPE pType);
PL_TYPE operator++(PL_TYPE pType);
PL_TYPE operator--(PL_TYPE pType);
