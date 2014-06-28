
#pragma once

OC_NS_BG;

class Vector2
{
public:
    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2& Vector);

    // Operations
    void clamp();
    void setZero();
    void normalize();
    float length(); //Magnitude

    Vector2& operator= (const Vector2& rhs);

    // Accessors
    float operator[] (uint32 pos) const;
    float& operator[] (uint32 pos);

    // Comparison
    bool operator== (const Vector2& vector) const;
    bool operator!= (const Vector2& vector)  const;

    // Arithmetic
    Vector2 operator+ (const Vector2& vector) const;
    Vector2 operator- (const Vector2& vector) const;
    Vector2 operator* (float scalar) const;
    Vector2 operator/ (float scalar) const;
    Vector2 operator- () const;

    Vector2& operator+= (const Vector2& vector);
    Vector2& operator-= (const Vector2& vector);
    Vector2& operator*= (float scalar);
    Vector2& operator/= (float scalar);

    float x;
    float y;
};

OC_NS_END;
