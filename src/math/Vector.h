
#pragma once


OC_NS_BG;

typedef DirectX::XMFLOAT2 XMFLOAT2;
typedef DirectX::XMFLOAT3 XMFLOAT3;
typedef DirectX::XMFLOAT4 XMFLOAT4;

// SIMD
typedef DirectX::FXMVECTOR FXMVECTOR;
typedef DirectX::XMVECTOR XMVECTOR;

struct Quaternion;
struct Matrix3;
struct Matrix4;


class Vector2 : public XMFLOAT2
{
public:
    Vector2();
    Vector2(float x, float y);
    Vector2(const XMFLOAT2& vector);
    Vector2(FXMVECTOR vector);

    Vector2& operator+=(const Vector2& other);
    Vector2 operator+(const Vector2& other) const;

    Vector2& operator-=(const Vector2& other);
    Vector2 operator-(const Vector2& other) const;

    Vector2& operator*=(const Vector2& other);
    Vector2 operator*(const Vector2& other) const;

    Vector2& operator/=(const Vector2& other);
    Vector2 operator/(const Vector2& other) const;

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    Vector2 operator-() const;

    operator XMVECTOR() const { return ToSIMD(); }
    XMVECTOR ToSIMD() const;

    static Vector2 Clamp(const Vector2& val, const Vector2& min, const Vector2& max);
    static float Length(const Vector2& val);
};


struct Vector3 : public XMFLOAT3
{
    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const XMFLOAT3& vector);
    Vector3(FXMVECTOR vector);

    Vector3& operator+=(const Vector3& other);
    Vector3 operator+(const Vector3& other) const;

    Vector3& operator+=(float other);
    Vector3 operator+(float other) const;

    Vector3& operator-=(const Vector3& other);
    Vector3 operator-(const Vector3& other) const;

    Vector3& operator-=(float other);
    Vector3 operator-(float other) const;

    Vector3& operator*=(const Vector3& s);
    Vector3 operator*(const Vector3& s) const;

    Vector3& operator*=(float other);
    Vector3 operator*(float other) const;

    Vector3& operator/=(const Vector3& other);
    Vector3 operator/(const Vector3& other) const;

    Vector3& operator/=(float other);
    Vector3 operator/(float other) const;

    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;

    Vector3 operator-() const;

    operator XMVECTOR() const { return ToSIMD(); }
    XMVECTOR ToSIMD() const;

    float Length() const;

    static float Dot(const Vector3& a, const Vector3& b);
    static Vector3 Cross(const Vector3& a, const Vector3& b);
    static Vector3 Normalize(const Vector3& a);
    static Vector3 Transform(const Vector3& v, const Matrix3& m);
    static Vector3 Transform(const Vector3& v, const Matrix4& m);
    static Vector3 TransformDirection(const Vector3&v, const Matrix4& m);
    static Vector3 Transform(const Vector3& v, const Quaternion& q);
    static Vector3 Clamp(const Vector3& val, const Vector3& min, const Vector3& max);
    static Vector3 Perpendicular(const Vector3& v);
    static float Distance(const Vector3& a, const Vector3& b);
    static float Length(const Vector3& v);
};


struct Vector4 : public XMFLOAT4
{
    Vector4();
    Vector4(float x);
    Vector4(float x, float y, float z, float w);
    Vector4(const XMFLOAT3& vec3, float w = 0.0f);
    Vector4(const XMFLOAT4& vec4);
    Vector4(FXMVECTOR vector);

    Vector4& operator+=(const Vector4& other);
    Vector4 operator+(const Vector4& other) const;

    Vector4& operator-=(const Vector4& other);
    Vector4 operator-(const Vector4& other) const;

    Vector4& operator*=(const Vector4& other);
    Vector4 operator*(const Vector4& other) const;

    Vector4& operator/=(const Vector4& other);
    Vector4 operator/(const Vector4& other) const;

    bool operator==(const Vector4& other) const;
    bool operator!=(const Vector4& other) const;

    Vector4 operator-() const;

    operator XMVECTOR() const { return ToSIMD(); }
    XMVECTOR ToSIMD() const;
    Vector3 ToVec3() const;

    static Vector4 Clamp(const Vector4& val, const Vector4& min, const Vector4& max);
};


struct Quaternion : public XMFLOAT4
{
    Quaternion();
    Quaternion(float roll, float pitch, float yaw);
    Quaternion(float x, float y, float z, float w);
    Quaternion(const Vector3& axis, float angle);
    Quaternion(const Matrix3& m);
    Quaternion(const XMFLOAT4& q);
    Quaternion(FXMVECTOR q);

    Quaternion& operator*=(const Quaternion& other);
    Quaternion operator*(const Quaternion& other) const;

    bool operator==(const Quaternion& other) const;
    bool operator!=(const Quaternion& other) const;

    Matrix3 ToMatrix3() const;
    Matrix4 ToMatrix4() const;

    static Quaternion Identity();
    static Quaternion Invert(const Quaternion& q);
    static Quaternion FromAxisAngle(const Vector3& axis, float angle);
    static Quaternion Normalize(const Quaternion& q);
    static Matrix3 ToMatrix3(const Quaternion& q);
    static Matrix4 ToMatrix4(const Quaternion& q);

    XMVECTOR ToSIMD() const;
};

OC_NS_END;
