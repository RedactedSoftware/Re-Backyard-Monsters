#include <Vector2.hpp>

namespace ReBackyardMonsters
{
    Vector2::Vector2()
    {
        this->X = 0;
        this->Y = 0;
    }
    Vector2::Vector2(float x, float y)
    {
        this->X = x;
        this->Y = y;
    }
    Vector2::Vector2(const Vector2& inp)
    {
        this->X = inp.X;
        this->Y = inp.Y;
    }

    Vector2 Vector2::Max(const Vector2& max) { }
    Vector2 Vector2::Min(const Vector2& max) { }
    Vector2 Vector2::Normal() { }
    Vector2 Vector2::Floor() { }
    Vector2 Vector2::Ceil() { }

    Vector2 Vector2::Clamp(const Vector2& min, const Vector2& max)
    {

    }

    Vector2 Vector2::Lerp(Vector2& goal, float alpha) const
    {

    }

    float Vector2::Dot(const Vector2 against)
    {

    }

    float Vector2::Magnitude() const
    {

    }

    float Vector2::Distance(const Vector2& to) const
    {

    }

    bool Vector2::operator==(const Vector2& rhs) const
    {

    }

    bool Vector2::operator!=(const Vector2& rhs) const
    {

    }

    Vector2 Vector2::operator+(const Vector2& rhs) const
    {

    }

    Vector2 Vector2::operator-(const Vector2& rhs) const
    {

    }

    Vector2 Vector2::operator*(const Vector2& rhs) const
    {

    }

    Vector2 Vector2::operator/(const Vector2& rhs) const
    {

    }

    Vector2 Vector2::operator*(const Vector2& rhs) const
    {

    }
}