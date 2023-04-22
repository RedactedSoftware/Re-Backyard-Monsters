#pragma once
namespace ReBackyardMonsters
{
    class Vector2
    {
    public:
        static const Vector2 Zero;
        static const Vector2 One;
        friend std::ostream& operator<< (std::ostream ofs, const Vector2& vector);

        Vector2();
        Vector2(float const& x, float const& y);
        Vector2(const Vector2& vec);
        float GetX() const { return this->X; }
        float GetY() const { return this->Y; }
        Vector2 Max(const Vector2& max);
        Vector2 Min(const Vector2& min);
        Vector2 Normal();
        Vector2 Floor();
        Vector2 Ceil();

        Vector2 Clamp(const Vector2& min, const Vector2& max);
        Vector2 Lerp(Vector2& goal, float alpha) const;
        Vector2 const Lerp(Vector2 const&start, Vector2 const&goal, float alpha) const;
        float Dot( Vector2 const&against);
        float Magnitude();
        const float Dot(Vector2 const&, Vector2 const&);
        const float Magnitude(Vector2 const&);
        float Distance(const Vector2& to) const;

        bool operator==(const Vector2& rhs) const;
        bool operator!=(const Vector2& rhs) const;
        Vector2& operator=(const Vector2&) = default;
        Vector2 operator+(const Vector2& rhs) const;
        Vector2 operator-(const Vector2& rhs) const;
        Vector2 operator*(const Vector2& rhs) const;
        Vector2 operator/(const Vector2& rhs) const;
        Vector2 operator*(float rhs) const;
        Vector2 operator/(float rhs) const;
    private:
        float X;
        float Y;
    };
}