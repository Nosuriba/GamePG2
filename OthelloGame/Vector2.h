#pragma once

#define U_INT (unsigned int)

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	~Vector2();

	int x, y;

	/* ‘ã“ü‰‰ŽZŽq */
	Vector2& operator = (const Vector2& vec);

	/* “Y‚¦Žš‰‰ŽZŽq(”z—ñ) */
	int operator[](int j);

	/* ”äŠr‰‰ŽZŽq */
	bool operator == (const Vector2& vec) const;
	bool operator != (const Vector2& vec) const;
	bool operator >  (const Vector2& vec) const;
	bool operator <  (const Vector2& vec) const;
	bool operator >= (const Vector2& vec) const;
	bool operator <= (const Vector2& vec) const;

	/* ’P€‰‰ŽZŽq */
	Vector2& operator += (const Vector2& vec);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator *= (int k);
	Vector2& operator /= (int k);
	Vector2 operator +() const;
	Vector2 operator -() const;
};

/* ƒxƒNƒgƒ‹“¯Žm‚Ì‰‰ŽZ */
// ‰ÁŽZ
Vector2 operator+(const Vector2& i, const Vector2& j);
// Œ¸ŽZ
Vector2 operator-(const Vector2& i, const Vector2& j);
// æŽZ
Vector2 operator*(const Vector2& i, int k);
Vector2 operator*(int k, const Vector2& i);
// œŽZ
Vector2 operator/(const Vector2& i, int k);


