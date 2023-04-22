#include <Vector2.hpp>
#include <ostream>
#include <sstream>
#include <cmath>

namespace ReBackyardMonsters
{
    inline Vector2::Vector2()
    {
        this->X = 0;
        this->Y = 0;
    }
    inline Vector2::Vector2(float const& x, float const& y) : X(x), Y(y) {}
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
    inline Vector2 Vector2::Lerp(Vector2& goal, float alpha) const
    {

    }
    inline Vector2 const Vector2::Lerp(Vector2 const&start, Vector2 const&goal, float alpha) const {

    }
    inline float Vector2::Dot(Vector2 const&against) {
        return this->X*against.X+this->Y*against.Y;
    }
    inline const float Vector2::Dot(Vector2 const&lhs, Vector2 const&rhs) {
        return lhs.X*rhs.X+lhs.Y*rhs.Y;
    }
    inline float Vector2::Magnitude()  {
        return sqrt(this->Dot(*this));
    }
    inline const float Vector2::Magnitude(Vector2 const&lhs) {
        return sqrt(Dot(lhs, lhs));
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
    inline Vector2 Vector2::operator+(const Vector2& rhs) const
    {
        return Vector2(this->X + rhs.X, this->Y+rhs.Y);
    }
    inline Vector2 Vector2::operator-(const Vector2& rhs) const
    {
        return Vector2(this->X - rhs.X, this->Y-rhs.Y);
    }
    inline Vector2 Vector2::operator*(const Vector2& rhs) const
    {
        return Vector2(this->X * rhs.X, this->Y * rhs.Y);
    }
    Vector2 Vector2::operator/(const Vector2& rhs) const
    {
        return Vector2(this->X / rhs.X, this->Y / rhs.Y);
    }
    Vector2 Vector2::operator/(float rhs) const
    {

    }

    Vector2 Vector2::operator*(float rhs) const
    {

    }
    // Fast Static members
    const Vector2 Vector2::Zero = Vector2(0,0);
    const Vector2 Vector2::One = Vector2(1, 1);

    inline const Vector2 operator-(Vector2 const&lhs, Vector2 const&rhs) {
        return Vector2(lhs.X-rhs.X, lhs.Y-rhs.Y);
    }
    inline const Vector2 operator+(Vector2 const&lhs, Vector2 const&rhs) {
        return Vector2(lhs.X+rhs.X, lhs.Y + rhs.Y);
    }
    inline const Vector2 operator/(Vector2 const&lhs, float const&rhs) {
        return Vector2(lhs.X/rhs, lhs.Y/rhs);
    }
    inline const Vector2 operator*(float lhs, Vector2 const &rhs) {
        return Vector2(rhs.X * lhs, rhs.Y * lhs);
    }
    inline const Vector2& operator-=(Vector2 &lhs, const Vector2 &rhs) {
        lhs.X-=rhs.X;
        lhs.Y-=rhs.Y;
        return lhs;
    }
    inline const Vector2& operator+=(Vector2 &lhs, const Vector2 &rhs) {
        lhs.X+=rhs.X;
        lhs.Y+=rhs.Y;
        return lhs;
    }
    inline const Vector2& operator/=(Vector2 &lhs, const Vector2& rhs) {
        lhs.X/=rhs.X;
        lhs.Y/=rhs.Y;
        return lhs;
    }
    inline const Vector2& operator*=(Vector2 &lhs, const Vector2 &rhs) {
        lhs.X*=rhs.X;
        lhs.Y*=rhs.Y;
        return lhs;
    }
    inline const Vector2& operator*=(Vector2 &lhs, const float &rhs)
    {
        lhs.X*=rhs;
        lhs.Y*=rhs;
        return lhs;
    }
    inline const bool operator!=(Vector2 const&lhs, Vector2 const&rhs) {
        return (lhs.X !=rhs.X) || (lhs.Y != rhs.Y);
    }
    constexpr float VectorEqualityMarginOfError = 0.000001f;
    inline const bool operator==(Vector2 const&lhs, Vector2 const&rhs) {
        return ((lhs.X*rhs.X<VectorEqualityMarginOfError)&&(lhs.Y * rhs.Y < VectorEqualityMarginOfError));
    }


}