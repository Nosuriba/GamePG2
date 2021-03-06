#pragma once

#define U_INT (unsigned int)

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	~Vector2();

	int x, y;

	// ������Z�q 
	Vector2& operator = (const Vector2& vec);

	// �Y�������Z�q(�z��) 
	int operator[](int j);

	// ��r���Z�q 
	bool operator == (const Vector2& vec) const;
	bool operator != (const Vector2& vec) const;
	bool operator >  (const Vector2& vec) const;
	bool operator <  (const Vector2& vec) const;
	bool operator >= (const Vector2& vec) const;
	bool operator <= (const Vector2& vec) const;

	// �P�����Z�q 
	Vector2& operator += (const Vector2& vec);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator *= (int k);
	Vector2& operator /= (int k);
	Vector2 operator +() const;
	Vector2 operator -() const;
};

// �x�N�g�����m�̉��Z 
// Vector2 + Vector2 
Vector2 operator+(const Vector2& i, const Vector2& j);
// Vector2 + int 
Vector2 operator+(const Vector2& i, int j);
// Vector2 - Vector2 
Vector2 operator-(const Vector2& i, const Vector2& j);
// Vector2 - int 
Vector2 operator-(const Vector2& i, int j);
// Vector2 * int 
Vector2 operator*(const Vector2& i, int k);
// int * Vector2 
Vector2 operator*(int k, const Vector2& i);
// Vector2 / int
Vector2 operator/(const Vector2& i, int k);


