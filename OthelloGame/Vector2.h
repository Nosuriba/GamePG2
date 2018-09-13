#pragma once

#define U_INT (unsigned int)

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	~Vector2();

	int x, y;

	/* ������Z�q */
	Vector2& operator = (const Vector2& vec);

	/* �Y�������Z�q(�z��) */
	int operator[](int j);

	/* ��r���Z�q */
	bool operator == (const Vector2& vec) const;
	bool operator != (const Vector2& vec) const;
	bool operator >  (const Vector2& vec) const;
	bool operator <  (const Vector2& vec) const;
	bool operator >= (const Vector2& vec) const;
	bool operator <= (const Vector2& vec) const;

	/* �P�����Z�q */
	Vector2& operator += (const Vector2& vec);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator *= (int k);
	Vector2& operator /= (int k);
	Vector2 operator +() const;
	Vector2 operator -() const;
};

/* �x�N�g�����m�̉��Z */
// ���Z
Vector2 operator+(const Vector2& i, const Vector2& j);
// ���Z
Vector2 operator-(const Vector2& i, const Vector2& j);
// ��Z
Vector2 operator*(const Vector2& i, int k);
Vector2 operator*(int k, const Vector2& i);
// ���Z
Vector2 operator/(const Vector2& i, int k);


