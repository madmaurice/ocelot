
#pragma once


OC_NS_BG;

struct Vector3;

typedef DirectX::XMFLOAT3X3 XMFLOAT3X3;
typedef DirectX::XMFLOAT4X4 XMFLOAT4X4;

// SIMD
typedef DirectX::FXMMATRIX FXMMATRIX;
typedef DirectX::XMMATRIX XMMATRIX;


struct Matrix3 : public XMFLOAT3X3
{
    Matrix3();
    Matrix3(const XMFLOAT3X3& m);
    Matrix3(FXMMATRIX m);

    Matrix3& operator*=(const Matrix3& other);
    Matrix3 operator*(const Matrix3& other) const;

    Vector3 Up() const;
    Vector3 Down() const;
    Vector3 Left() const;
    Vector3 Right() const;
    Vector3 Forward() const;
    Vector3 Back() const;

    void SetXBasis(const Vector3& x);
    void SetYBasis(const Vector3& y);
    void SetZBasis(const Vector3& z);

    Matrix3 Transpose() const;
    Matrix3 Inverse() const;

    static Matrix3 Transpose(const Matrix3& m);
    static Matrix3 Inverse(const Matrix3& m);
    static Matrix3 RotationX(float angle);
    static Matrix3 RotationY(float angle);
    static Matrix3 RotationZ(float angle);
    static Matrix3 ScaleMatrix(float s);
    static Matrix3 ScaleMatrix(const Vector3& s);

    operator XMMATRIX() const { return ToSIMD(); }
    XMMATRIX ToSIMD() const;
};


struct Matrix4 : public XMFLOAT4X4
{
    Matrix4();
    Matrix4(const XMFLOAT4X4& m);
    Matrix4(FXMMATRIX m);

    Matrix4& operator*=(const Matrix4& other);
    Matrix4 operator*(const Matrix4& other) const;

    Vector3 Up() const;
    Vector3 Down() const;
    Vector3 Left() const;
    Vector3 Right() const;
    Vector3 Forward() const;
    Vector3 Back() const;

    Vector3 GetTranslation() const;
    void SetTranslation(const Vector3& t);

    void SetXBasis(const Vector3& x);
    void SetYBasis(const Vector3& y);
    void SetZBasis(const Vector3& z);

    Matrix4 Transpose() const;
    Matrix4 Inverse() const;

    static Matrix4 Transpose(const Matrix4& m);
    static Matrix4 Inverse(const Matrix4& m);
    static Matrix4 RotationX(float angle);
    static Matrix4 RotationY(float angle);
    static Matrix4 RotationZ(float angle);
    static Matrix4 ScaleMatrix(float s);
    static Matrix4 ScaleMatrix(const Vector3& s);
    static Matrix4 TranslationMatrix(const Vector3& t);

    static Matrix4 LookAtMatrixLH(const Vector3& eye, const Vector3& lookAt, const Vector3& up);
    static Matrix4 PerspectiveFovMatrixLH(float aspectRatio, float fov, float nearClip, float farClip);

    operator XMMATRIX() const { return ToSIMD(); }
    XMMATRIX ToSIMD() const;

    std::string Print() const;
};

OC_NS_END;