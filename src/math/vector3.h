
#pragma once

OC_NS_BG;

class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector3& vector);

    // Operations
    Vector3 cross(const Vector3& A) const;
    float dot(const Vector3& A) const;
    void clamp();
    void setZero();
    float length(); // Magnitude
    void normalize();
    Vector3 perpendicular();

    // Static operations
    static Vector3 clamp(const Vector3& A);
    static Vector3 cross(const Vector3& A, const Vector3& B);
    static float dot(const Vector3& A, const Vector3& B);
    static Vector3 normalize(const Vector3& A);
    static Vector3 perpendicular(const Vector3& A);
    static Vector3 random();

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