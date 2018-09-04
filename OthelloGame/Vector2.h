#pragma once

#define U_INT (unsigned int)

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	~Vector2();

	int x, y;

	/* ‘ã“ü‰‰Zq */
	Vector2& operator = (const Vector2& vec);

	/* “Y‚¦š‰‰Zq(”z—ñ) */
	int operator[](int j);

	/* ”äŠr‰‰Zq */
	bool operator == (const Vector2& vec) const;
	bool operator != (const Vector2& vec) const;

	/* ’P€‰‰Zq */
	Vector2& operator += (const Vector2& vec);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator *= (int k);
	Vector2& operator /= (int k);
	Vector2 operator +() const;
	Vector2 operator -() const;
};

/* ƒxƒNƒgƒ‹“¯m‚Ì‰‰Z */
// ‰ÁZ
Vector2 operator+(const Vector2& i, const Vector2& j);
// Œ¸Z
Vector2 operator-(const Vector2& i, const Vector2& j);
// æZ
Vector2 operator*(const Vector2& i, int k);
Vector2 operator*(int k, const Vector2& i);
// œZ
Vector2 operator/(const Vector2& i, int k);


