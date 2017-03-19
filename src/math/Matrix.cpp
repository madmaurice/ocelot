
#include "Matrix.h"
#include "Vector.h"
#include "math/Math.h"

using namespace DirectX;

OC_NS_BG;

//  Matrix3 ------------------------------------------------------

Matrix3::Matrix3()
{
    XMStoreFloat3x3(this, XMMatrixIdentity());
}

Matrix3::Matrix3(const XMFLOAT3X3& m)
{
    *static_cast<XMFLOAT3X3*>(this) = m;
}

Matrix3::Matrix3(FXMMATRIX m)
{
    XMStoreFloat3x3(this, m);
}

Matrix3& Matrix3::operator*=(const Matrix3& other)
{
    XMMATRIX result = this->ToSIMD() * other.ToSIMD();
    XMStoreFloat3x3(this, result);
    return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& other) const
{
    XMMATRIX result = this->ToSIMD() * other.ToSIMD();
    return Matrix3(result);
}

Vector3 Matrix3::Up() const
{
    return Vector3(_21, _22, _23);
}

Vector3 Matrix3::Down() const
{
    return Vector3(-_21, -_22, -_23);
}

Vector3 Matrix3::Left() const
{
    return Vector3(-_11, -_12, -_13);
}

Vector3 Matrix3::Right() const
{
    return Vector3(_11, _12, _13);
}

Vector3 Matrix3::Forward() const
{
    return Vector3(_31, _32, _33);
}

Vector3 Matrix3::Back() const
{
    return Vector3(-_31, -_32, -_33);
}

void Matrix3::SetXBasis(const Vector3& x)
{
    _11 = x.x;
    _12 = x.y;
    _13 = x.z;
}

void Matrix3::SetYBasis(const Vector3& y)
{
    _21 = y.x;
    _22 = y.y;
    _23 = y.z;
}

void Matrix3::SetZBasis(const Vector3& z)
{
    _31 = z.x;
    _32 = z.y;
    _33 = z.z;
}

Matrix3 Matrix3::Transpose() const
{
    return XMMatrixTranspose(*this);
}

Matrix3 Matrix3::Inverse() const
{
    XMVECTOR det;
    return XMMatrixInverse(&det, *this);
}

Matrix3 Matrix3::RotationX(float angle)
{
    return XMMatrixRotationX(angle);
}

Matrix3 Matrix3::RotationY(float angle)
{
    return XMMatrixRotationY(angle);
}

Matrix3 Matrix3::RotationZ(float angle)
{
    return XMMatrixRotationZ(angle);
}

Matrix3 Matrix3::Transpose(const Matrix3& m)
{
    return m.Transpose();
}

Matrix3 Matrix3::Inverse(const Matrix3& m)
{
    return m.Inverse();
}

Matrix3 Matrix3::ScaleMatrix(float s)
{
    Matrix3 m;
    m._11 = m._22 = m._33 = s;
    return m;
}

Matrix3 Matrix3::ScaleMatrix(const Vector3& s)
{
    Matrix3 m;
    m._11 = s.x;
    m._22 = s.y;
    m._33 = s.z;
    return m;
}

XMMATRIX Matrix3::ToSIMD() const
{
    return XMLoadFloat3x3(this);
}


//  Matrix4 ------------------------------------------------------

Matrix4::Matrix4()
{
    XMStoreFloat4x4(this, XMMatrixIdentity());
}

Matrix4::Matrix4(const XMFLOAT4X4& m)
{
    *static_cast<XMFLOAT4X4*>(this) = m;
}

Matrix4::Matrix4(FXMMATRIX m)
{
    XMStoreFloat4x4(this, m);
}

Matrix4& Matrix4::operator*=(const Matrix4& other)
{
    XMMATRIX result = this->ToSIMD() * other.ToSIMD();
    XMStoreFloat4x4(this, result);
    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
    XMMATRIX result = this->ToSIMD() * other.ToSIMD();
    return Matrix4(result);
}

Vector3 Matrix4::Up() const
{
    return Vector3(_21, _22, _23);
}

Vector3 Matrix4::Down() const
{
    return Vector3(-_21, -_22, -_23);
}

Vector3 Matrix4::Left() const
{
    return Vector3(-_11, -_12, -_13);
}

Vector3 Matrix4::Right() const
{
    return Vector3(_11, _12, _13);
}

Vector3 Matrix4::Forward() const
{
    return Vector3(_31, _32, _33);
}

Vector3 Matrix4::Back() const
{
    return Vector3(-_31, -_32, -_33);
}

Vector3 Matrix4::GetTranslation() const
{
    return Vector3(_41, _42, _43);
}

void Matrix4::SetTranslation(const Vector3& t)
{
    _41 = t.x;
    _42 = t.y;
    _43 = t.z;
}

void Matrix4::SetXBasis(const Vector3& x)
{
    _11 = x.x;
    _12 = x.y;
    _13 = x.z;
}

void Matrix4::SetYBasis(const Vector3& y)
{
    _21 = y.x;
    _22 = y.y;
    _23 = y.z;
}

void Matrix4::SetZBasis(const Vector3& z)
{
    _31 = z.x;
    _32 = z.y;
    _33 = z.z;
}

Matrix4 Matrix4::Transpose() const
{
    return XMMatrixTranspose(*this);
}

Matrix4 Matrix4::Inverse() const
{
    XMVECTOR det;
    return XMMatrixInverse(&det, *this);
}

Matrix4 Matrix4::Transpose(const Matrix4& m)
{
    return m.Transpose();
}

Matrix4 Matrix4::Inverse(const Matrix4& m)
{
    return m.Inverse();
}

Matrix4 Matrix4::RotationX(float angle)
{
    return XMMatrixRotationX(angle);
}

Matrix4 Matrix4::RotationY(float angle)
{
    return XMMatrixRotationY(angle);
}

Matrix4 Matrix4::RotationZ(float angle)
{
    return XMMatrixRotationZ(angle);
}

Matrix4 Matrix4::ScaleMatrix(float s)
{
    Matrix4 m;
    m._11 = m._22 = m._33 = s;
    return m;
}

Matrix4 Matrix4::ScaleMatrix(const Vector3& s)
{
    Matrix4 m;
    m._11 = s.x;
    m._22 = s.y;
    m._33 = s.z;
    return m;
}

Matrix4 Matrix4::TranslationMatrix(const Vector3& t)
{
    Matrix4 m;
    m.SetTranslation(t);
    return m;
}

Matrix4 Matrix4::LookAtMatrixLH(const Vector3& eye, const Vector3& lookAt, const Vector3& up)
{
    Matrix4 m(XMMatrixLookAtLH(eye, lookAt, up));
    return m;
}

Matrix4 Matrix4::PerspectiveFovMatrixLH(float aspectRatio, float fov, float nearClip, float farClip)
{
    Matrix4 m(XMMatrixPerspectiveFovLH(fov, aspectRatio, nearClip, farClip));
    return m;
}

XMMATRIX Matrix4::ToSIMD() const
{
    return XMLoadFloat4x4(this);
}

std::string Matrix4::Print() const
{
    std::stringstream sstream;
    sstream << "{ "  << _11 << _12 << _13 << _14 << "}\n";
    sstream << "{ " << _21 << _22 << _23 << _24 << "}\n";
    sstream << "{ " << _31 << _32 << _33 << _34 << "}\n";
    sstream << "{ " << _41 << _42 << _43 << _44 << "}\n }";
    return sstream.str();
}

OC_NS_END;