
#pragma once

OC_NS_BG;

class Vector2;
class Vector3;

class Vector4
{
public:
    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(const Vector3& vector, float w);
    Vector4(const Vector4& vector);

    // Operations
    void Clamp();
    float Dot(Vector4& vector);
    void SetZero();
    void Normalize();
    float Length(); // Magnitude

    Vector4& operator= (const Vector4& vector);

    // Accessors
    float operator[] (uint32 pos) const;
    float& operator[] (uint32 pos);

    // Comparison
    bool operator== (const Vector4& vector) const;
    bool operator!= (const Vector4& vector) const;

    // Arithmetic
    Vector4 operator+ (const Vector4& vector) const;
    Vector4 operator- (const Vector4& vector) const;
    Vector4 operator* (float fScalar) const;
    Vector4 operator* (const Vector4& vector) const;
    Vector4 operator/ (float fScalar) const;
    Vector4 operator/ (const Vector4& vector) const;
    Vector4 operator- () const;

    Vector4& operator+= (const Vector4& vector);
    Vector4& operator-= (const Vector4& vector);
    Vector4& operator*= (float fScalar);
    Vector4& operator*= (const Vector4& vector);
    Vector4& operator/= (float fScalar);
    Vector4& operator/= (const Vector4& vector);

    uint32 ToARGB();
    uint32 ToRGBA();

    void FromARGB(uint32 color);

    Vector3 xyz() const;
    Vector2 xy() const;

    float x;
    float y;
    float z;
    float w;
};

OC_NS_END;