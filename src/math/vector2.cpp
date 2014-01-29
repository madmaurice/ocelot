
#include "vector2.h"
#include <cmath>

OC_NS_BG;

Vector2::Vector2()
{
}

Vector2::Vector2(float X, float Y)
{
	x = X;
	y = Y;
}

Vector2::Vector2(const Vector2& vector)
{
	x = vector.x;
	y = vector.y;
}

Vector2& Vector2::operator= (const Vector2& rhs)
{
	x = rhs.x;
	y = rhs.y;

    return *this;
}

void Vector2::setZero()
{
	x = 0.0f;
	y = 0.0f;
}

void Vector2::normalize()
{
	float invMag = (1.0f / length());

	x *= invMag;
	y *= invMag;
}

float Vector2::length()
{
	float length = 0.0f;

	length += x * x;
	length += y * y;

	return sqrtf(length);
}

void Vector2::clamp()
{
	if ( x > 1.0f ) x = 1.0f;
	if ( x < 0.0f ) x = 0.0f;

	if ( y > 1.0f ) y = 1.0f;
	if ( y < 0.0f ) y = 0.0f;
}

float Vector2::operator[] (uint32 pos) const
{
    return pos == 0 ? x : y;
}

float& Vector2::operator[] (uint32 pos)
{
    return pos == 0 ? x : y;
}

bool Vector2::operator== (const Vector2& vector) const
{
	if ( (x - vector.x) * (x - vector.x) > 0.01f )
		return false;
	if ( (y - vector.y) * (y - vector.y) > 0.01f )
		return false;

	return true;
}

bool Vector2::operator!= (const Vector2& vector) const
{
    return !( *this == vector );
}

Vector2 Vector2::operator+ (const Vector2& vector) const
{
	Vector2 sum;

	sum.x = x + vector.x;
	sum.y = y + vector.y;

	return sum;
}

Vector2 Vector2::operator- (const Vector2& vector) const
{
	Vector2 diff;

	diff.x = x - vector.x;
	diff.y = y - vector.y;

	return diff;
}

Vector2 Vector2::operator* (float scalar) const
{
	Vector2 prod;

	prod.x = x * scalar;
	prod.y = y * scalar;

	return prod;
}

Vector2 Vector2::operator/ (float scalar) const
{
	Vector2 quot;
	if ( scalar != 0.0f )
	{
		float invScalar = 1.0f / scalar;
		quot.x = x * invScalar;
		quot.y = y * invScalar;
	}
	else
	{
		quot.setZero();
	}

	return quot;
}

Vector2 Vector2::operator- () const
{
	Vector2 neg;

	neg.x = -x;
	neg.y = -y;

	return neg;
}

Vector2& Vector2::operator+= (const Vector2& vector)
{
	x += vector.x;
	y += vector.y;

	return *this;
}

Vector2& Vector2::operator-= (const Vector2& vector)
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

Vector2& Vector2::operator*= (float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2& Vector2::operator/= (float scalar)
{
	if ( scalar != 0.0f )
	{
		float invScalar = 1.0f / scalar;	
		x *= invScalar;
		y *= invScalar;
	}
	else
	{
		setZero();
	}

	return *this;
}

OC_NS_END;
