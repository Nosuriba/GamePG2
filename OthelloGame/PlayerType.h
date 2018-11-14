#pragma once

// ÉvÉåÉCÉÑÅ[ÇÃéÌóﬁ
enum class PL_TYPE
{
	PL_MAN,
	PL_CPU,
	PL_MAX
};

PL_TYPE begin(PL_TYPE);
PL_TYPE end(PL_TYPE);
PL_TYPE operator*(PL_TYPE type);
PL_TYPE operator++(PL_TYPE type);
PL_TYPE operator--(PL_TYPE type);