#pragma once

#include <string>
#include <regex>
#include <cstdlib>

typedef uint8_t uint8;
typedef int8_t int8;

namespace ReBackyardMonsters
{
    class Color3
    {
    public:
        float R;
        float G;
        float B;
        float A;
        Color3() {}
        Color3(float r, float g, float b) : R(r), G(g), B(b) {}
        Color3(float r, float g, float b, float a) : R(r),G(g),B(b),A(a) { }
        static Color3 fromRGB(uint8 r, uint8 g, uint8 b);
        static Color3 fromRGBA(uint8 r, uint8 g, uint8 b);
        static Color3 fromHSV(float h, float s, float v);
        static Color3 fromHSVA(float h, float s, float v, float a);
        static Color3 fromHex(std::string hexLiteral);
        static Color3 random();
        float GetRed() const;
        float GetGreen() const;
        float GetBlue() const;
        float GetAlpha() const;
        uint8_t GetIntegerRed() const;
        uint8_t GetIntegerGreen() const;
        uint8_t GetIntegerBlue() const;
        uint8_t GetIntegerAlpha() const;
        bool operator==(Color3 const&other) const;
        bool operator!=(Color3 const&other) const;
    };
};