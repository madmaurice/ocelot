
#pragma once

#include <d3dx11.h>
#include <dxerr.h>

#if defined(OC_DEBUG)

#define DXCall(x)                                              \
    __pragma(warning(push))                                    \
    __pragma(warning(disable:4127))                            \
    do                                                         \
    {                                                          \
        HRESULT hr = (x);                                      \
        if(FAILED(hr))                                         \
        {                                                      \
            DXTrace(__FILE__, (DWORD)__LINE__, hr, #x, true);  \
            __debugbreak();                                    \
        }                                                      \
    }                                                          \
    while(0)                                                   \
    __pragma(warning(pop))
#else
#define DXCall(x) (x)
#endif // OC_DEBUG

#include "math/math.h"

OC_NS_BG;

#define COLORGLOBAL const extern __declspec(selectany)

namespace Colors
{
    COLORGLOBAL Vector4 IndianRed = { 0.804f, 0.361f, 0.361f, 1.0f };
    COLORGLOBAL Vector4 LightCoral = { 0.941f, 0.502f, 0.502f, 1.0f };
    COLORGLOBAL Vector4 Salmon = { 0.980f, 0.502f, 0.447f, 1.0f };
    COLORGLOBAL Vector4 DarkSalmon = { 0.914f, 0.588f, 0.478f, 1.0f };
    COLORGLOBAL Vector4 LightSalmon = { 1.0f, 0.627f, 0.478f, 1.0f };
    COLORGLOBAL Vector4 Crimson = { 0.863f, 0.078f, 0.235f, 1.0f };
    COLORGLOBAL Vector4 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 FireBrick = { 0.698f, 0.133f, 0.133f, 1.0f };
    COLORGLOBAL Vector4 DarkRed = { 0.545f, 0.0f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 Pink = { 1.0f, 0.753f, 0.796f, 1.0f };
    COLORGLOBAL Vector4 LightPink = { 1.0f, 0.714f, 0.747f, 1.0f };
    COLORGLOBAL Vector4 HotPink = { 1.0f, 0.412f, 0.706f, 1.0f };
    COLORGLOBAL Vector4 DeepPink = { 1.0f, 0.078f, 0.576f, 1.0f };
    COLORGLOBAL Vector4 MediumVioletRed = { 0.780f, 0.082f, 0.522f, 1.0f };
    COLORGLOBAL Vector4 PaleVioletRed = { 0.859f, 0.439f, 0.576f, 1.0f };
    COLORGLOBAL Vector4 Coral = { 1.0f, 0.627f, 0.478f, 1.0f };
    COLORGLOBAL Vector4 Tomato = { 1.0f, 0.388f, 0.278f, 1.0f };
    COLORGLOBAL Vector4 OrangeRed = { 1.0f, 0.271f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 DarkOrange = { 1.0f, 0.549f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 Orange = { 1.0f, 0.647f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 Gold = { 1.0f, 0.843f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 LightYellow = { 1.0f, 1.0f, 0.878f, 1.0f };
    COLORGLOBAL Vector4 LemonChion = { 0.980f, 0.980f, 0.804f, 1.0f };
    COLORGLOBAL Vector4 LightGoldenRodYellow = { 0.980f, 0.980f, 0.824f, 1.0f };
    COLORGLOBAL Vector4 PapayaWhip = { 1.0f, 0.937f, 0.835f, 1.0f };
    COLORGLOBAL Vector4 Moccasin = { 1.0f, 0.894f, 0.710f, 1.0f };
    COLORGLOBAL Vector4 PeachPu = { 1.0f, 0.855f, 0.725f, 1.0f };
    COLORGLOBAL Vector4 PaleGoldenRod = { 0.933f, 0.910f, 0.667f, 1.0f };
    COLORGLOBAL Vector4 Khaki = { 0.941f, 0.902f, 0.549f, 1.0f };
    COLORGLOBAL Vector4 DarkKhaki = { 0.741f, 0.718f, 0.420f, 1.0f };
    COLORGLOBAL Vector4 Lavender = { 0.902f, 0.902f, 0.980f, 1.0f };
    COLORGLOBAL Vector4 Thistle = { 0.847f, 0.749f, 0.847f, 1.0f };
    COLORGLOBAL Vector4 Plum = { 0.867f, 0.627f, 0.867f, 1.0f };
    COLORGLOBAL Vector4 Violet = { 0.933f, 0.510f, 0.933f, 1.0f };
    COLORGLOBAL Vector4 Orchid = { 0.655f, 0.439f, 0.839f, 1.0f };
    COLORGLOBAL Vector4 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 MediumOrchid = { 0.729f, 0.333f, 0.827f, 1.0f };
    COLORGLOBAL Vector4 MediumPurple = { 0.576f, 0.439f, 0.859f, 1.0f };
    COLORGLOBAL Vector4 BlueViolet = { 0.541f, 0.169f, 0.886f, 1.0f };
    COLORGLOBAL Vector4 DarkViolet = { 0.580f, 0.0f, 0.827f, 1.0f };
    COLORGLOBAL Vector4 DarkOrchid = { 0.600f, 0.196f, 0.800f, 1.0f };
    COLORGLOBAL Vector4 DarkMagenta = { 0.545f, 0.0f, 0.545f, 1.0f };
    COLORGLOBAL Vector4 Purple = { 0.502f, 0.0f, 0.502f, 1.0f };
    COLORGLOBAL Vector4 Indigo = { 0.294f, 0.0f, 0.510f, 1.0f };
    COLORGLOBAL Vector4 SlateBlue = { 0.416f, 0.353f, 0.804f, 1.0f };
    COLORGLOBAL Vector4 DarkSlateBlue = { 0.282f, 0.239f, 0.545f, 1.0f };
    COLORGLOBAL Vector4 GreenYellow = { 0.678f, 1.0f, 0.184f, 1.0f };
    COLORGLOBAL Vector4 Chartreuse = { 0.498f, 1.0f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 LawnGreen = { 0.486f, 0.988f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 Lime = { 0.0f, 1.0f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 LimeGreen = { 0.196f, 0.804f, 0.196f, 1.0f };
    COLORGLOBAL Vector4 PaleGreen = { 0.596f, 0.984f, 0.596f, 1.0f };
    COLORGLOBAL Vector4 LightGreen = { 0.565f, 0.933f, 0.565f, 1.0f };
    COLORGLOBAL Vector4 MediumSpringGreen = { 0.0f, 0.980f, 0.604f, 1.0f };
    COLORGLOBAL Vector4 SpringGreen = { 0.0f, 1.0f, 0.498f, 1.0f };
    COLORGLOBAL Vector4 MediumSeaGreen = { 0.235f, 0.702f, 0.443f, 1.0f };
    COLORGLOBAL Vector4 SeaGreen = { 0.180f, 0.545f, 0.341f, 1.0f };
    COLORGLOBAL Vector4 ForestGreen = { 0.133f, 0.545f, 0.133f, 1.0f };
    COLORGLOBAL Vector4 Green = { 0.0f, 0.502f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 DarkGreen = { 0.0f, 0.392f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 YellowGreen = { 0.604f, 0.804f, 0.196f, 1.0f };
    COLORGLOBAL Vector4 OliveDrab = { 0.420f, 0.557f, 0.137f, 1.0f };
    COLORGLOBAL Vector4 Olive = { 0.502f, 0.502f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 DarkOliveGreen = { 0.333f, 0.420f, 0.184f, 1.0f };
    COLORGLOBAL Vector4 MediumAquamarine = { 0.400f, 0.804f, 0.667f, 1.0f };
    COLORGLOBAL Vector4 DarkSeaGreen = { 0.561f, 0.737f, 0.561f, 1.0f };
    COLORGLOBAL Vector4 LightSeaGreen = { 0.125f, 0.698f, 0.667f, 1.0f };
    COLORGLOBAL Vector4 DarkCyan = { 0.0f, 0.545f, 0.545f, 1.0f };
    COLORGLOBAL Vector4 Teal = { 0.0f, 0.502f, 0.502f, 1.0f };
    COLORGLOBAL Vector4 Aqua = { 0.0f, 1.0f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 LightCyan = { 0.878f, 1.0f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 PaleTurquoise = { 0.686f, 0.933f, 0.933f, 1.0f };
    COLORGLOBAL Vector4 Aquamarine = { 0.498f, 1.0f, 0.831f, 1.0f };
    COLORGLOBAL Vector4 Turquoise = { 0.251f, 0.878f, 0.816f, 1.0f };
    COLORGLOBAL Vector4 MediumTurquoise = { 0.282f, 0.820f, 0.800f, 1.0f };
    COLORGLOBAL Vector4 DarkTurquoise = { 0.0f, 0.808f, 0.820f, 1.0f };
    COLORGLOBAL Vector4 CadetBlue = { 0.373f, 0.620f, 0.627f, 1.0f };
    COLORGLOBAL Vector4 SteelBlue = { 0.275f, 0.510f, 0.706f, 1.0f };
    COLORGLOBAL Vector4 LightSteelBlue = { 0.690f, 0.769f, 0.871f, 1.0f };
    COLORGLOBAL Vector4 LightBlue = { 0.678f, 0.847f, 0.902f, 1.0f };
    COLORGLOBAL Vector4 PowderBlue = { 0.690f, 0.878f, 0.902f, 1.0f };
    COLORGLOBAL Vector4 SkyBlue = { 0.529f, 0.808f, 0.922f, 1.0f };
    COLORGLOBAL Vector4 LightSkyBlue = { 0.529f, 0.808f, 0.980f, 1.0f };
    COLORGLOBAL Vector4 DeepSkyBlue = { 0.0f, 0.749f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 DodgerBlue = { 0.118f, 0.565f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 CornflowerBlue = { 0.392f, 0.584f, 0.929f, 1.0f };
    COLORGLOBAL Vector4 MediumSlateBlue = { 0.482f, 0.408f, 0.933f, 1.0f };
    COLORGLOBAL Vector4 RoyalBlue = { 0.255f, 0.412f, 0.882f, 1.0f };
    COLORGLOBAL Vector4 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 MediumBlue = { 0.0f, 0.0f, 0.804f, 1.0f };
    COLORGLOBAL Vector4 DarkBlue = { 0.0f, 0.0f, 0.545f, 1.0f };
    COLORGLOBAL Vector4 Navy = { 0.0f, 0.0f, 0.502f, 1.0f };
    COLORGLOBAL Vector4 MidnightBlue = { 0.098f, 0.098f, 0.439f, 1.0f };
    COLORGLOBAL Vector4 Cornsilk = { 1.0f, 0.973f, 0.863f, 1.0f };
    COLORGLOBAL Vector4 BlanchedAlmond = { 1.0f, 0.922f, 0.804f, 1.0f };
    COLORGLOBAL Vector4 Bisque = { 1.0f, 0.894f, 0.769f, 1.0f };
    COLORGLOBAL Vector4 NavajoWhite = { 1.0f, 0.871f, 0.678f, 1.0f };
    COLORGLOBAL Vector4 Wheat = { 0.961f, 0.871f, 0.702f, 1.0f };
    COLORGLOBAL Vector4 BurlyWood = { 0.871f, 0.722f, 0.529f, 1.0f };
    COLORGLOBAL Vector4 Tan = { 0.824f, 0.706f, 0.549f, 1.0f };
    COLORGLOBAL Vector4 RosyBrown = { 0.737f, 0.561f, 0.561f, 1.0f };
    COLORGLOBAL Vector4 SandyBrown = { 0.957f, 0.643f, 0.376f, 1.0f };
    COLORGLOBAL Vector4 Goldenrod = { 0.855f, 0.647f, 0.125f, 1.0f };
    COLORGLOBAL Vector4 DarkGoldenrod = { 0.722f, 0.525f, 0.043f, 1.0f };
    COLORGLOBAL Vector4 Peru = { 0.804f, 0.522f, 0.247f, 1.0f };
    COLORGLOBAL Vector4 Chocolate = { 0.824f, 0.412f, 0.118f, 1.0f };
    COLORGLOBAL Vector4 SaddleBrown = { 0.545f, 0.271f, 0.075f, 1.0f };
    COLORGLOBAL Vector4 Sienna = { 0.627f, 0.322f, 0.176f, 1.0f };
    COLORGLOBAL Vector4 Brown = { 0.647f, 0.165f, 0.165f, 1.0f };
    COLORGLOBAL Vector4 Maroon = { 0.502f, 0.0f, 0.0f, 1.0f };
    COLORGLOBAL Vector4 White = { 1.0f, 1.0f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 Snow = { 1.0f, 0.980f, 0.980f, 1.0f };
    COLORGLOBAL Vector4 Honeydew = { 0.941f, 1.0f, 0.941f, 1.0f };
    COLORGLOBAL Vector4 MintCream = { 0.961f, 1.0f, 0.980f, 1.0f };
    COLORGLOBAL Vector4 Azure = { 0.941f, 1.0f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 AliceBlue = { 0.941f, 0.973f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 GhostWhite = { 0.973f, 0.973f, 1.0f, 1.0f };
    COLORGLOBAL Vector4 WhiteSmoke = { 0.961f, 0.961f, 0.961f, 1.0f };
    COLORGLOBAL Vector4 SeaShell = { 1.0f, 0.961f, 0.933f, 1.0f };
    COLORGLOBAL Vector4 Beige = { 0.961f, 0.961f, 0.863f, 1.0f };
    COLORGLOBAL Vector4 OldLace = { 0.992f, 0.961f, 0.902f, 1.0f };
    COLORGLOBAL Vector4 FloralWhite = { 1.0f, 0.980f, 0.941f, 1.0f };
    COLORGLOBAL Vector4 Ivory = { 1.0f, 1.0f, 0.941f, 1.0f };
    COLORGLOBAL Vector4 AntiqueWhite = { 0.980f, 0.922f, 0.843f, 1.0f };
    COLORGLOBAL Vector4 Linen = { 0.980f, 0.941f, 0.902f, 1.0f };
    COLORGLOBAL Vector4 LavenderBlush = { 1.0f, 0.941f, 0.961f, 1.0f };
    COLORGLOBAL Vector4 MistyRose = { 1.0f, 0.894f, 0.882f, 1.0f };
    COLORGLOBAL Vector4 Gainsboro = { 0.863f, 0.863f, 0.863f, 1.0f };
    COLORGLOBAL Vector4 LightGrey = { 0.827f, 0.827f, 0.827f, 1.0f };
    COLORGLOBAL Vector4 Silver = { 0.753f, 0.753f, 0.753f, 1.0f };
    COLORGLOBAL Vector4 DarkGrey = { 0.663f, 0.663f, 0.633f, 1.0f };
    COLORGLOBAL Vector4 Gray = { 0.502f, 0.502f, 0.502f, 1.0f };
    COLORGLOBAL Vector4 DimGray = { 0.412f, 0.412f, 0.412f, 1.0f };
    COLORGLOBAL Vector4 LightSlateGray = { 0.467f, 0.533f, 0.600f, 1.0f };
    COLORGLOBAL Vector4 SlateGray = { 0.439f, 0.502f, 0.565f, 1.0f };
    COLORGLOBAL Vector4 DarkSlateGray = { 0.184f, 0.310f, 0.310f, 1.0f };
    COLORGLOBAL Vector4 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
}

#undef COLORGLOBAL

OC_NS_END;