
#pragma once

#include "Vector3.h"

OC_NS_BG;

class Matrix3
{
public:
    Matrix3();
    explicit Matrix3(bool toZero);
    Matrix3(const Matrix3& matrix);
    Matrix3(float n11, float n12, float n13,
            float n21, float n22, float n23,
            float n31, float n32, float n33);
    
    void RotationX(float radians);
    void RotationY(float radians);
    void RotationZ(float radians);
    void Rotation(Vector3& rot);
    void RotationZYX(Vector3& rot);
    void RotationEuler(Vector3& axis, float angle);
    void Orthonormalize();

    void SetZero();
    void SetIdentity();
    void SetTranspose();

    Matrix3 Zero();
    Matrix3 Identity();
    Matrix3 Transpose();

    // Operators
    Matrix3& operator= (const Matrix3& matrix);

    // Member access
    float operator() (uint32 row, uint32 col) const;
    float& operator() (uint32 row, uint32 col);
    float operator[] (uint32 pos) const;
    float& operator[] (uint32 pos);

    void SetRow(uint32 row, const Vector3& vector);
    Vector3 GetRow(uint32 row) const;
    void SetColumn(uint32 col, const Vector3& vector);
    Vector3 GetColumn(uint32 col) const;

    // Comparison
    bool operator== (const Matrix3& matrix) const;
    bool operator!= (const Matrix3& matrix) const;

    // Arithmetic operations
    Matrix3 operator+ (const Matrix3& matrix) const;
    Matrix3 operator- (const Matrix3& matrix) const;
    Matrix3 operator* (const Matrix3& matrix) const;
    Matrix3 operator* (float scalar) const;
    Matrix3 operator/ (float scalar) const;
    Matrix3 operator- () const;

    Matrix3& operator+= (const Matrix3& matrix);
    Matrix3& operator-= (const Matrix3& matrix);
    Matrix3& operator*= (const Matrix3& matrix);
    Matrix3& operator*= (float scalar);
    Matrix3& operator/= (float scalar);

    // Matrix - vector operations
    Vector3 operator* (const Vector3& rkV) const;  // M * v

    // Elements constant
    static const uint32 m11 = 0;
    static const uint32 m12 = 1;
    static const uint32 m13 = 2;

    static const uint32 m21 = 3;
    static const uint32 m22 = 4;
    static const uint32 m23 = 5;

    static const uint32 m31 = 6;
    static const uint32 m32 = 7;
    static const uint32 m33 = 8;

protected:
    float m_data[3*3];

    static uint32 Index(uint32 row, uint32 col); // row*N + col
};

OC_NS_END;