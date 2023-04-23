#include <Color3.hpp>

namespace ReBackyardMonsters
{
    Color3 Color3::fromRGB(uint8_t r, uint8_t g, uint8_t b) {
        return Color3(r / 255.0f, g / 255.0f, b / 255.0f);
    }
    Color3 Color3::fromHSV(float h, float s, float v) {
        if (s == 0) {
            return Color3(v,v,v);
        }
        int i = h * 6.0;
        float f = (h * 6.0) - i;
        float p = v * (1.0 - s);
        float q = v * (1.0 - s * f);
        float t = v * (1.0 - s * (1.0 - f));
        i = i % 6;

        float r, g, b;
        switch (i) {
            case 0:
                r = v;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = v;
                b = p;
                break;
            case 2:
                r = p;
                g = v;
                b = t;
                break;

            case 3:
                r = p;
                g = q;
                b = v;
                break;
            case 4:
                r = t;
                g = p;
                b = v;
                break;
            case 5:
            default:
                r = v;
                g = p;
                b = q;
                break;
        }
        return Color3(r, g, b);
    }
    Color3 Color3::fromHex(std::string hexLiteral) {
        std::regex pattern("#?([0-9a-fA-F]{2})([0-9a-fA-F]{2})([0-9a-fA-F]{2})");

        std::smatch match;
        if (std::regex_match(hexLiteral, match, pattern)) {
            unsigned long r = std::stoul(match[1].str(), nullptr, 16);
            unsigned long g = std::stoul(match[2].str(), nullptr, 16);
            unsigned long b = std::stoul(match[3].str(), nullptr, 16);
            return Color3::fromRGB(r, g, b);
        }
        throw std::runtime_error("Hex color code is not valid");
    }
}