
#include "Vector.h"
#include "Matrix.h"
#include "math/Math.h"

#include <algorithm>

using namespace DirectX;

OC_NS_BG;

//  Vector2 --------------------------------------

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(float ax, float ay)
{
    x = ax;
    y = ay;
}

Vector2::Vector2(const XMFLOAT2& vector)
{
    x = vector.x;
    y = vector.y;
}

Vector2::Vector2(FXMVECTOR vector)
{
    XMStoreFloat2(this, vector);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    Vector2 result;
    result.x = x + other.x;
    result.y = y + other.y;
    return result;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    Vector2 result;
    result.x = x - other.x;
    result.y = y - other.y;
    return result;
}

Vector2& Vector2::operator*=(const Vector2& other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector2 Vector2::operator*(const Vector2& other) const
{
    Vector2 result;
    result.x = x * other.x;
    result.y = y * other.y;
    return result;
}

Vector2& Vector2::operator/=(const Vector2& other)
{
    x /= other.x;
    y /= other.y;
    return *this;
}

Vector2 Vector2::operator/(const Vector2& other) const
{
    Vector2 result;
    result.x = x / other.x;
    result.y = y / other.y;
    return result;
}

bool Vector2::operator==(const Vector2& other) const
{
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const
{
    return x != other.x || y != other.y;
}

Vector2 Vector2::operator-() const
{
    Vector2 result;
    result.x = -x;
    result.y = -y;

    return result;
}

XMVECTOR Vector2::ToSIMD() const
{
    return XMLoadFloat2(this);
}

Vector2 Vector2::Clamp(const Vector2& val, const Vector2& min, const Vector2& max)
{
    Vector2 retVal;
    retVal.x = OC::Clamp(val.x, min.x, max.x);
    retVal.y = OC::Clamp(val.y, min.y, max.y);
    return retVal;
}

float Vector2::Length(const Vector2& val)
{
    return std::sqrtf(val.x * val.x + val.y * val.y);
}

//  Vector3 --------------------------------------

Vector3::Vector3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(float ax, float ay, float az)
{
    x = ax;
    y = ay;
    z = az;
}

Vector3::Vector3(const XMFLOAT3& vector)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
}

Vector3::Vector3(FXMVECTOR vector)
{
    XMStoreFloat3(this, vector);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    Vector3 result;
    result.x = x + other.x;
    result.y = y + other.y;
    result.z = z + other.z;
    return result;
}

Vector3& Vector3::operator+=(float s)
{
    x += s;
    y += s;
    z += s;
    return *this;
}

Vector3 Vector3::operator+(float s) const
{
    Vector3 result;
    result.x = x + s;
    result.y = y + s;
    result.z = z + s;
    return result;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    Vector3 result;
    result.x = x - other.x;
    result.y = y - other.y;
    result.z = z - other.z;
    return result;
}

Vector3& Vector3::operator-=(float s)
{
    x -= s;
    y -= s;
    z -= s;
    return *this;
}

Vector3 Vector3::operator-(float s) const
{
    Vector3 result;
    result.x = x - s;
    result.y = y - s;
    result.z = z - s;
    return result;
}

Vector3& Vector3::operator*=(const Vector3& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Vector3 Vector3::operator*(const Vector3& other) const
{
    Vector3 result;
    result.x = x * other.x;
    result.y = y * other.y;
    result.z = z * other.z;
    return result;
}

Vector3& Vector3::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vector3 Vector3::operator*(float s) const
{
    Vector3 result;
    result.x = x * s;
    result.y = y * s;
    result.z = z * s;
    return result;
}

Vector3& Vector3::operator/=(const Vector3& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

Vector3 Vector3::operator/(const Vector3& other) const
{
    Vector3 result;
    result.x = x / other.x;
    result.y = y / other.y;
    result.z = z / other.z;
    return result;
}

Vector3& Vector3::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

Vector3 Vector3::operator/(float s) const
{
    Vector3 result;
    result.x = x / s;
    result.y = y / s;
    result.z = z / s;
    return result;
}

bool Vector3::operator==(const Vector3& other) const
{
    return x == other.x && y == other.y && z == other.z;
}

bool Vector3::operator!=(const Vector3& other) const
{
    return x != other.x || y != other.y || z != other.z;
}

Vector3 Vector3::operator-() const
{
    Vector3 result;
    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}

Vector3 operator*(float a, const Vector3& b)
{
    return Vector3(a * b.x, a * b.y, a * b.z);
}

XMVECTOR Vector3::ToSIMD() const
{
    return XMLoadFloat3(this);
}

float Vector3::Length() const
{
    return Vector3::Length(*this);
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
    return XMVectorGetX(XMVector3Dot(a.ToSIMD(), b.ToSIMD()));
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
    Vector3 result;
    XMStoreFloat3(&result, XMVector3Cross(a.ToSIMD(), b.ToSIMD()));
    return result;
}

Vector3 Vector3::Normalize(const Vector3& a)
{
    Vector3 result;
    XMStoreFloat3(&result, XMVector3Normalize(a.ToSIMD()));
    return result;
}

Vector3 Vector3::Transform(const Vector3& v, const Matrix3& m)
{
    XMVECTOR vec = v.ToSIMD();
    vec = XMVector3TransformCoord(vec, m.ToSIMD());
    return Vector3(vec);
}

Vector3 Vector3::Transform(const Vector3& v, const Matrix4& m)
{
    XMVECTOR vec = v.ToSIMD();
    vec = XMVector3TransformCoord(vec, m.ToSIMD());
    return Vector3(vec);
}

Vector3 Vector3::TransformDirection(const Vector3&v, const Matrix4& m)
{
    XMVECTOR vec = v.ToSIMD();
    vec = XMVector3TransformNormal(vec, m.ToSIMD());
    return Vector3(vec);
}

Vector3 Vector3::Transform(const Vector3& v, const Quaternion& q)
{
    return Vector3::Transform(v, q.ToMatrix3());
}

Vector3 Vector3::Clamp(const Vector3& val, const Vector3& min, const Vector3& max)
{
    Vector3 retVal;
    retVal.x = OC::Clamp(val.x, min.x, max.x);
    retVal.y = OC::Clamp(val.y, min.y, max.y);
    retVal.z = OC::Clamp(val.z, min.z, max.z);
    return retVal;
}

Vector3 Vector3::Perpendicular(const Vector3& vec)
{
    OC_ASSERT(vec.Length() >= 0.00001f);

    Vector3 perp;

    float x = std::abs(vec.x);
    float y = std::abs(vec.y);
    float z = std::abs(vec.z);
    float minVal = std::min(x, y);
    minVal = std::min(minVal, z);

    if(minVal == x)
        perp = Vector3::Cross(vec, Vector3(1.0f, 0.0f, 0.0f));
    else if(minVal == y)
        perp = Vector3::Cross(vec, Vector3(0.0f, 1.0f, 0.0f));
    else
        perp = Vector3::Cross(vec, Vector3(0.0f, 0.0f, 1.0f));

    return Vector3::Normalize(perp);
}

float Vector3::Distance(const Vector3& a, const Vector3& b)
{
    XMVECTOR x = XMLoadFloat3(&a);
    XMVECTOR y = XMLoadFloat3(&b);
    XMVECTOR length = XMVector3Length(XMVectorSubtract(x, y));
    return XMVectorGetX(length);
}

float Vector3::Length(const Vector3& v)
{
    XMVECTOR x =  XMLoadFloat3(&v);
    XMVECTOR length = XMVector3Length(x);
    return XMVectorGetX(length);
}

//  Vector4 --------------------------------------

Vector4::Vector4()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

Vector4::Vector4(float ax, float ay, float az, float aw)
{
    x = ax;
    y = ay;
    z = az;
    w = aw;
}

Vector4::Vector4(const XMFLOAT3& vec3, float aw)
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
    w = aw;
}

Vector4::Vector4(const XMFLOAT4& vec4)
{
    x = vec4.x;
    y = vec4.y;
    z = vec4.z;
    w = vec4.w;
}

Vector4::Vector4(FXMVECTOR vector)
{
    XMStoreFloat4(this, vector);
}

Vector4& Vector4::operator+=(const Vector4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Vector4 Vector4::operator+(const Vector4& other) const
{
    Vector4 result;
    result.x = x + other.x;
    result.y = y + other.y;
    result.z = z + other.z;
    result.w = w + other.w;
    return result;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Vector4 Vector4::operator-(const Vector4& other) const
{
    Vector4 result;
    result.x = x - other.x;
    result.y = y - other.y;
    result.z = z - other.z;
    result.w = w - other.w;
    return result;
}

Vector4& Vector4::operator*=(const Vector4& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
}

Vector4 Vector4::operator*(const Vector4& other) const
{
    Vector4 result;
    result.x = x * other.x;
    result.y = y * other.y;
    result.z = z * other.z;
    result.w = w * other.w;
    return result;
}

Vector4& Vector4::operator/=(const Vector4& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;
    return *this;
}

Vector4 Vector4::operator/(const Vector4& other) const
{
    Vector4 result;
    result.x = x / other.x;
    result.y = y / other.y;
    result.z = z / other.z;
    result.w = w / other.w;
    return result;
}

bool Vector4::operator==(const Vector4& other) const
{
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vector4::operator!=(const Vector4& other) const
{
    return x != other.x || y != other.y || z != other.z || w != other.w;
}

Vector4 Vector4::operator-() const
{
    Vector4 result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;

    return result;
}

XMVECTOR Vector4::ToSIMD() const
{
    return XMLoadFloat4(this);
}

Vector3 Vector4::ToVec3() const
{
    return Vector3(x, y, z);
}

Vector4 Vector4::Clamp(const Vector4& val, const Vector4& min, const Vector4& max)
{
    Vector4 retVal;
    retVal.x = OC::Clamp(val.x, min.x, max.x);
    retVal.y = OC::Clamp(val.y, min.y, max.y);
    retVal.z = OC::Clamp(val.z, min.z, max.z);
    retVal.w = OC::Clamp(val.w, min.w, max.w);
    return retVal;
}

//  Quaternion --------------------------------------

Quaternion::Quaternion()
{
    *this = Quaternion::Identity();
}

Quaternion::Quaternion(float roll, float pitch, float yaw)
{
    *this = XMQuaternionRotationRollPitchYaw(roll, pitch, yaw);
}

Quaternion::Quaternion(float ax, float ay, float az, float aw)
{
    x = ax;
    y = ay;
    z = az;
    w = aw;
}

Quaternion::Quaternion(const Vector3& axis, float angle)
{
    *this = Quaternion::FromAxisAngle(axis, angle);
}

Quaternion::Quaternion(const Matrix3& m)
{
    *this = XMQuaternionRotationMatrix(m.ToSIMD());
}

Quaternion::Quaternion(const XMFLOAT4& q)
{
    x = q.x;
    y = q.y;
    z = q.z;
    w = q.w;
}

Quaternion::Quaternion(FXMVECTOR q)
{
    XMStoreFloat4(this, q);
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
    XMVECTOR q = ToSIMD();
    q = XMQuaternionMultiply(q, other.ToSIMD());
    XMStoreFloat4(this, q);

    return *this;
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
    Quaternion q = *this;
    q *= other;
    return q;
}

bool Quaternion::operator==(const Quaternion& other) const
{
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Quaternion::operator!=(const Quaternion& other) const
{
    return x != other.x || y != other.y || z != other.z || w != other.w;
}

Matrix3 Quaternion::ToMatrix3() const
{
    return Matrix3(XMMatrixRotationQuaternion(ToSIMD()));
}

Matrix4 Quaternion::ToMatrix4() const
{
    return Matrix4(XMMatrixRotationQuaternion(ToSIMD()));
}

Quaternion Quaternion::Identity()
{
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::Invert(const Quaternion& q)
{
    return Quaternion(XMQuaternionInverse(q.ToSIMD()));
}

Quaternion Quaternion::FromAxisAngle(const Vector3& axis, float angle)
{
    XMVECTOR q = XMQuaternionRotationAxis(axis.ToSIMD(), angle);
    return Quaternion(q);
}

Quaternion Quaternion::Normalize(const Quaternion& q)
{
    return Quaternion(XMQuaternionNormalize(q.ToSIMD()));
}

Matrix3 Quaternion::ToMatrix3(const Quaternion& q)
{
    return q.ToMatrix3();
}

Matrix4 Quaternion::ToMatrix4(const Quaternion& q)
{
    return q.ToMatrix4();
}

XMVECTOR Quaternion::ToSIMD() const
{
    return XMLoadFloat4(this);
}

OC_NS_END;
