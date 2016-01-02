
#pragma once

OC_NS_BG;

class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector3& vector);

    // Operations
    Vector3 Cross(const Vector3& A) const;
    float Dot(const Vector3& A) const;
    void Clamp();
    void SetZero();
    float Length(); // Magnitude
    void Normalize();
    Vector3 Perpendicular();

    // Static operations
    static Vector3 Clamp(const Vector3& A);
    static Vector3 Cross(const Vector3& A, const Vector3& B);
    static float Dot(const Vector3& A, const Vector3& B);
    static Vector3 Normalize(const Vector3& A);
    static Vector3 Perpendicular(const Vector3& A);
    static Vector3 Random();

    Vector3& operator= (const Vector3& vector);

    // Accessors
    float operator[] (uint32 pos) const;
    float& operator[] (uint32 pos);

    // Comparison
    bool operator== (const Vector3& vector) const;
    bool operator!= (const Vector3& vector) const;

    // Arithmetic
    Vector3 operator+ (const Vector3& vector) const;
    Vector3 operator- (const Vector3& vector) const;
    Vector3 operator* (const Vector3& vector) const;
    Vector3 operator* (float scalar) const;
    Vector3 operator/ (const Vector3& vector) const;
    Vector3 operator/ (float scalar) const;
    Vector3 operator- () const;

    Vector3& operator+= (const Vector3& vector);
    Vector3& operator-= (const Vector3& vector);
    Vector3& operator*= (const Vector3& vector);
    Vector3& operator*= (float scalar);
    Vector3& operator/= (const Vector3& vector);
    Vector3& operator/= (float scalar);

    float x;
    float y;
    float z;
};

OC_NS_END;