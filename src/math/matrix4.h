
#pragma once

#include "matrix3.h"
#include "vector4.h"

OC_NS_BG;

class Matrix4
{
public:

    Matrix4();
    explicit Matrix4(bool toZero);
    Matrix4(const Matrix4& matrix);
    Matrix4(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44);
    Matrix4 inverse() const;

    void rotationX(float radians);
    void rotationY(float radians);
    void rotationZ(float radians);
    void scale(float scale);
    void translate(float x, float y, float z);

    // Returns first 3 members of a row (discard w row)
    Vector3 getBasisX() const;
    Vector3 getBasisY() const;
    Vector3 getBasisZ() const;

    Vector3 getTranslation() const;
    Matrix3 getRotation() const;

    void setRotation(const Matrix3& Rot);
    void setTranslation(const Vector3& Trans);

    static Matrix4 rotationMatrixX(float radians);
    static Matrix4 rotationMatrixY(float radians);
    static Matrix4 rotationMatrixZ(float radians);
    static Matrix4 scaleMatrix(float scale);
    static Matrix4 scaleMatrix(const Vector3& scale);
    static Matrix4 scaleMatrixXYZ(float x, float y, float z);
    static Matrix4 translationMatrix(float x, float y, float z);
    static Matrix4 lookAtLHMatrix(Vector3& eye, Vector3& at, Vector3& up);
    static Matrix4 perspectiveFovLHMatrix(float fovy, float aspect, float zn, float zf);
    static Matrix4 orthographicLHMatrix(float zn, float zf, float width, float height);

    void setZero();
    void setIdentity();
    void setTranspose();

    static Matrix4 zero();
    static Matrix4 identity();
    Matrix4 transpose();

    // Operators
    Matrix4& operator= (const Matrix4& matrix);

    // Accessors
    float operator() (uint32 row, uint32 col) const;
    float& operator() (uint32 row, uint32 col);
    float operator[] (uint32 pos) const;
    float& operator[] (uint32 pos);

    void setRow(uint32 row, const Vector4& vector);
    void setRow(uint32 row, const Vector3& vector);		
    Vector4 getRow(uint32 row) const;        
    void setColumn(uint32 col, const Vector4& vector);
    Vector4 getColumn(uint32 col) const;

    // Comparison
    bool operator== (const Matrix4& matrix) const;
    bool operator!= (const Matrix4& matrix) const;

    // Arithmetic
    Matrix4 operator+ (const Matrix4& matrix) const;
    Matrix4 operator- (const Matrix4& matrix) const;
    Matrix4 operator* (const Matrix4& matrix) const;
    Matrix4 operator* (float scalar) const;
    Matrix4 operator/ (float scalar) const;
    Matrix4 operator- () const;

    Matrix4& operator+= (const Matrix4& matrix);
    Matrix4& operator-= (const Matrix4& matrix);
    Matrix4& operator*= (const Matrix4& matrix);
    Matrix4& operator*= (float scalar);
    Matrix4& operator/= (float scalar);

    // Matrix - vector operations
    Vector4 operator* (const Vector4& V) const;  // M * v

    // Elements constant
    static const uint32 m11 = 0;
    static const uint32 m12 = 1;
    static const uint32 m13 = 2;
    static const uint32 m14 = 3;

    static const uint32 m21 = 4;
    static const uint32 m22 = 5;
    static const uint32 m23 = 6;
    static const uint32 m24 = 7;
    
    static const uint32 m31 = 8;
    static const uint32 m32 = 9;
    static const uint32 m33 = 10;
    static const uint32 m34 = 11;

    static const uint32 m41 = 12;
    static const uint32 m42 = 13;
    static const uint32 m43 = 14;
    static const uint32 m44 = 15;

protected:
    float m_data[4*4];

    // Get the array index for row and col
    static uint32 index(uint32 row, uint32 col); // row*N + col
};

OC_NS_END;