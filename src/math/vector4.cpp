
#include "vector4.h"
#include "vector3.h"
#include "vector2.h"
#include <cmath>

OC_NS_BG;

Vector4::Vector4()
    : x(0)
    , y(0)
    , z(0)
    , w(0)
{
}

Vector4::Vector4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4::Vector4(const Vector3& vector, float w)
{
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
    this->w = w;
}

Vector4::Vector4(const Vector4& vector)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
    w = vector.w;
}

Vector4& Vector4::operator= (const Vector4& vector)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
    w = vector.w;

    return *this;
}

void Vector4::setZero()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

void Vector4::normalize()
{
    float invMag = ( 1.0f / length() );

    x *= invMag;
    y *= invMag;
    z *= invMag;
    w *= invMag;
}

float Vector4::length()
{
    float length = 0.0f;

    length += x * x;
    length += y * y;
    length += z * z;
    length += w * w;

    return( sqrt(length) );
}

float Vector4::dot(Vector4& vector)
{
    float ret = 0.0f;

    ret += x * vector.x;
    ret += y * vector.y;
    ret += z * vector.z;
    ret += w * vector.w;

    return ret;
}

float Vector4::operator[] (uint32 pos) const
{
    if ( pos == 0 ) return( x );
    if ( pos == 1 ) return( y );
    if ( pos == 2 ) return( z );
    return w;
}

float& Vector4::operator[] (uint32 pos)
{
    if ( pos == 0 ) return( x );
    if ( pos == 1 ) return( y );
    if ( pos == 2 ) return( z );
    return w;
}

bool Vector4::operator== ( const Vector4& vector ) const
{

    if ( ( x - vector.x ) * ( x - vector.x ) > 0.01f )
        return false;
    if ( ( y - vector.y ) * ( y - vector.y ) > 0.01f )
        return false;
    if ( ( z - vector.z ) * ( z - vector.z ) > 0.01f )
        return false;
    if ( ( w - vector.w ) * ( w - vector.w ) > 0.01f )
        return false;

    return true;
}

bool Vector4::operator!= (const Vector4& vector) const
{
    return !( *this == vector );
}

Vector4 Vector4::operator+ (const Vector4& vector) const
{
    Vector4 sum;

    sum.x = x + vector.x;
    sum.y = y + vector.y;
    sum.z = z + vector.z;
    sum.w = w + vector.w;

    return( sum );
}

Vector4 Vector4::operator- (const Vector4& vector) const
{
    Vector4 diff;

    diff.x = x - vector.x;
    diff.y = y - vector.y;
    diff.z = z - vector.z;
    diff.w = w - vector.w;

    return( diff );
}

Vector4 Vector4::operator* (float fScalar) const
{
    Vector4 prod;

    prod.x = x * fScalar;
    prod.y = y * fScalar;
    prod.z = z * fScalar;
    prod.w = w * fScalar;

    return( prod );
}

Vector4 Vector4::operator* (const Vector4& vector) const
{
    Vector4 prod;

    prod.x = x * vector.x;
    prod.y = y * vector.y;
    prod.z = z * vector.z;
    prod.w = w * vector.w;

    return( prod );
}

Vector4 Vector4::operator/ (float scalar) const
{
    Vector4 quot;
    if ( scalar != 0.0f )
    {
        float invScalar = 1.0f / scalar;
        quot.x = x * invScalar;
        quot.y = y * invScalar;
        quot.z = z * invScalar;
        quot.w = w * invScalar;
    }
    else
    {
        quot.setZero();
    }

    return( quot );
}

Vector4 Vector4::operator/ (const Vector4& vector) const
{
    Vector4 quot;
    quot.x = vector.x != 0.0f ? x / vector.x : 0.0f;
    quot.y = vector.y != 0.0f ? y / vector.y : 0.0f;
    quot.z = vector.z != 0.0f ? z / vector.z : 0.0f;
    quot.w = vector.w != 0.0f ? w / vector.w : 0.0f;

    return( quot );
}

Vector4 Vector4::operator- () const
{
    Vector4 neg;

    neg.x = -x;
    neg.y = -y;
    neg.z = -z;
    neg.w = -w;

    return neg;
}

Vector4& Vector4::operator+= (const Vector4& vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    w += vector.w;

    return *this;
}

Vector4& Vector4::operator-= (const Vector4& vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    w -= vector.w;

    return *this;
}

Vector4& Vector4::operator*= (float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

Vector4& Vector4::operator*= (const Vector4& vector)
{
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;
    w *= vector.w;

    return *this;
}

Vector4& Vector4::operator/= (float scalar)
{
    if ( scalar != 0.0f )
    {
        float invScalar = 1.0f / scalar;	
        x *= invScalar;
        y *= invScalar;
        z *= invScalar;
        w *= invScalar;
    }
    else
    {
        setZero();
    }

    return *this;
}

Vector4& Vector4::operator/= (const Vector4& vector)
{
    x = vector.x != 0.0f ? x / vector.x : 0.0f;
    y = vector.y != 0.0f ? y / vector.y : 0.0f;
    z = vector.z != 0.0f ? z / vector.z : 0.0f;
    w = vector.w != 0.0f ? w / vector.w : 0.0f;

    return *this;
}

void Vector4::clamp()
{
    if ( x > 1.0f ) x = 1.0f;
    if ( x < 0.0f ) x = 0.0f;

    if ( y > 1.0f ) y = 1.0f;
    if ( y < 0.0f ) y = 0.0f;

    if ( z > 1.0f ) z = 1.0f;
    if ( z < 0.0f ) z = 0.0f;

    if ( w > 1.0f ) w = 1.0f;
    if ( w < 0.0f ) w = 0.0f;
}

uint32 Vector4::toARGB()
{
    uint32 result = 0;

    clamp();

    result += (uint32)(255 * z);
    result += ((uint32)(255 * y) << 8);
    result += ((uint32)(255 * x) << 16);
    result += ((uint32)(255 * w) << 24);

    return( result );
}

uint32 Vector4::toRGBA()
{
    uint32 result = 0;

    clamp();

    result += (uint32)(255 * w);
    result += ((uint32)(255 * z) << 8);
    result += ((uint32)(255 * y) << 16);
    result += ((uint32)(255 * x) << 24);

    return( result );
}

void Vector4::fromARGB(uint32 color)
{
    x = (float)((color & 0x00ff0000) >> 16)/(255.0f);	// red channel
    y = (float)((color & 0x0000ff00) >> 8)/(255.0f);	// green channel
    z = (float)((color & 0x000000ff))/(255.0f);		// blue channel
    w = (float)((color & 0xff000000) >> 24)/(255.0f);	// alpha channel
}

Vector3 Vector4::xyz() const
{
    return Vector3(x, y, z);
}

Vector2 Vector4::xy() const
{
    return Vector2(x, y);
}

OC_NS_END;