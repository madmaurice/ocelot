
#pragma once

#include "vector3.h"
#include "core/defines.h"
#include "core/types.h"

OC_NS_BG;

class Matrix3
{
public:
    Matrix3();
    explicit Matrix3(bool toZero);
    Matrix3(const Matrix3& matrix);
    Matrix3(float m11, float m12, float m13,
            float m21, float m22, float m23,
            float m31, float m32, float m33);
    
    void rotationX(float radians);
    void rotationY(float radians);
    void rotationZ(float radians);
    void rotation(Vector3& rot);
    void rotationZYX(Vector3& rot);
    void rotationEuler(Vector3& axis, float angle);
    void orthonormalize();

    void setZero();
    void setIdentity();
    void setTranspose();

    Matrix3 zero();
    Matrix3 identity();
    Matrix3 transpose();

    // Operators
    Matrix3& operator= (const Matrix3& matrix);

    // Member access
    float operator() (uint32 row, uint32 col) const;
    float& operator() (uint32 row, uint32 col);
    float operator[] (uint32 pos) const;
    float& operator[] (uint32 pos);

    void setRow(uint32 row, const Vector3& vector);
    Vector3 getRow(uint32 row) const;
    void setColumn(uint32 col, const Vector3& vector);
    Vector3 getColumn(uint32 col) const;

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

    static uint32 index(uint32 row, uint32 col); // row*N + col
};

OC_NS_END;