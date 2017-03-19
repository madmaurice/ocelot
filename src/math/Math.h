
#pragma once

#define OC_PI               3.141592654f
#define OC_2PI              6.283185307f
#define OC_1DIVPI           0.318309886f
#define OC_1DIV2PI          0.159154943f
#define OC_PIDIV2           1.570796327f
#define OC_PIDIV4           0.785398163f

#include "Vector.h"
#include "Matrix.h"

OC_NS_BG;

// Linear interpolation
template<typename T>
T Lerp(const T& x, const T& y, float s)
{
    return x + (y - x) * s;
}

// Clamps a value to the specified range
template<typename T>
T Clamp(T val, T min, T max)
{
    OC_ASSERT(max >= min);

    if (val < min)
        val = min;
    else if (val > max)
        val = max;
    return val;
}

// Clamps a value to [0, 1]
template<typename T>
T Saturate(T val)
{
    return Clamp<T>(val, T(0.0f), T(1.0f));
}

// Rounds a float
inline float Round(float r)
{
    return (r > 0.0f) ? std::floorf(r + 0.5f) : std::ceilf(r - 0.5f);
}

// Returns a random float value between 0 and 1
inline float RandFloat()
{
    return rand() / static_cast<float>(RAND_MAX);
}

OC_NS_END;