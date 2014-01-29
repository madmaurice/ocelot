
#include "vector3.h"
#include <cmath>
#include <algorithm>

OC_NS_BG;

Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

void Vector3::setZero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

void Vector3::normalize()
{
	float mag = length();
	if ( 0.0f == mag ) mag = 0.0001f;

	float invMag = ( 1.0f / mag );

	x *= invMag;
	y *= invMag;
	z *= invMag;
}

float Vector3::length()
{
	float length = 0.0f;

	length += x * x;
	length += y * y;
	length += z * z;

	return sqrt(length);
}

Vector3 Vector3::perpendicular()
{
    float xAbs = fabs( x );
    float yAbs = fabs( y );
    float zAbs = fabs( z );
    float minVal = std::min( std::min( xAbs, yAbs ), zAbs );

    if ( xAbs == minVal )
        return cross( Vector3( 1.0f, 0.0f, 0.0f ) );
    else if ( yAbs == minVal )
        return cross( Vector3( 0.0f, 1.0f, 0.0f ) );
    else
        return cross( Vector3( 0.0f, 0.0f, 1.0f ) );
}

Vector3 Vector3::cross(const Vector3& vector) const
{
	Vector3 ret; 
	
	ret.x = y * vector.z - z * vector.y;
	ret.y = z * vector.x - x * vector.z;
	ret.z = x * vector.y - y * vector.x;
	
	return ret;
}

float Vector3::dot(const Vector3& vector) const
{
	float ret = 0.0f;
	
	ret  = x * vector.x;
	ret += y * vector.y;
	ret += z * vector.z;

	return ret;
}

void Vector3::clamp()
{
	if ( x > 1.0f ) x = 1.0f;
	if ( x < 0.0f ) x = 0.0f;

	if ( y > 1.0f ) y = 1.0f;
	if ( y < 0.0f ) y = 0.0f;

	if ( z > 1.0f ) z = 1.0f;
	if ( z < 0.0f ) z = 0.0f;
}

Vector3 Vector3::random()
{
	float x = static_cast<float>( (double)rand() / RAND_MAX ) * 2.0f - 1.0f;
	float y = static_cast<float>( (double)rand() / RAND_MAX ) * 2.0f - 1.0f;
	float z = static_cast<float>( (double)rand() / RAND_MAX ) * 2.0f - 1.0f;
	
	Vector3 random = Vector3( x, y, z );
	random.normalize();

	return random;
}

Vector3& Vector3::operator= (const Vector3& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;

    return *this;
}

float Vector3::operator[] (uint32 pos) const
{
	if ( pos == 0 ) return( x );
	if ( pos == 1 ) return( y );
	return z;
}

float& Vector3::operator[] (uint32 pos)
{
	if ( pos == 0 ) return( x );
	if ( pos == 1 ) return( y );
	return z;
}

bool Vector3::operator== (const Vector3& vector) const
{

	if ( ( x - vector.x ) * ( x - vector.x ) > 0.01f )
		return false;
	if ( ( y - vector.y ) * ( y - vector.y ) > 0.01f )
		return false;
	if ( ( z - vector.z ) * ( z - vector.z ) > 0.01f )
		return false;

	return true;
}

bool Vector3::operator!= (const Vector3& vector) const
{
    return !( *this == vector );
}

Vector3 Vector3::operator+ (const Vector3& vector) const
{
	Vector3 sum;

	sum.x = x + vector.x;
	sum.y = y + vector.y;
	sum.z = z + vector.z;

	return sum;
}

Vector3 Vector3::operator- (const Vector3& vector) const
{
	Vector3 diff;

	diff.x = x - vector.x;
	diff.y = y - vector.y;
	diff.z = z - vector.z;

	return diff;
}

Vector3 Vector3::operator* (float scalar) const
{
	Vector3 prod;

	prod.x = x * scalar;
	prod.y = y * scalar;
	prod.z = z * scalar;

	return prod;
}

Vector3 Vector3::operator* (const Vector3& vector) const
{
    Vector3 prod;

    prod.x = x * vector.x;
    prod.y = y * vector.y;
    prod.z = z * vector.z;

    return prod;
}

Vector3 Vector3::operator/ (float scalar) const
{
	Vector3 quot;
	if ( scalar != 0.0f )
	{
		float invScalar = 1.0f / scalar;
		quot.x = x * invScalar;
		quot.y = y * invScalar;
		quot.z = z * invScalar;
	}
	else
	{
		quot.setZero();
	}

	return quot;
}

Vector3 Vector3::operator/ (const Vector3& vector) const
{
    Vector3 quot;
    quot.x = vector.x != 0.0f ? x / vector.x : 0.0f;
    quot.y = vector.y != 0.0f ? y / vector.y : 0.0f;
    quot.z = vector.z != 0.0f ? z / vector.z : 0.0f;

    return quot;
}

Vector3 Vector3::operator- () const
{
	Vector3 neg;

	neg.x = -x;
	neg.y = -y;
	neg.z = -z;

	return neg;
}

Vector3& Vector3::operator+= (const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

Vector3& Vector3::operator-= (const Vector3& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

Vector3& Vector3::operator*= (float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3& Vector3::operator*= (const Vector3& vector)
{
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;

    return *this;
}

Vector3& Vector3::operator/= (float scalar)
{
	if ( scalar != 0.0f )
	{
		float fInvScalar = 1.0f / scalar;	
		x *= fInvScalar;
		y *= fInvScalar;
		z *= fInvScalar;
	}
	else
	{
		setZero();
	}

	return *this;
}

Vector3& Vector3::operator/= (const Vector3& vector)
{
    x = vector.x != 0.0f ? x / vector.x : 0.0f;
    y = vector.y != 0.0f ? y / vector.y : 0.0f;
    z = vector.z != 0.0f ? z / vector.z : 0.0f;

    return *this;
}

Vector3 Vector3::clamp(const Vector3& A)
{
    Vector3 vec = A;
    vec.clamp();
    return vec;
}

Vector3 Vector3::cross(const Vector3& A, const Vector3& B)
{    
    return A.cross(B);
}

float Vector3::dot(const Vector3& A, const Vector3& B)
{    
    return A.dot(B);
}

Vector3 Vector3::normalize(const Vector3& A)
{
    Vector3 vec = A;
    vec.normalize();
    return vec;
}

Vector3 Vector3::perpendicular(const Vector3& A)
{
    Vector3 vec = A;
    return vec.perpendicular();    
}

OC_NS_END;