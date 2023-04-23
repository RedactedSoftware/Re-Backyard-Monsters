#pragma once

#include <Vector2.hpp>

namespace ReBackyardMonsters
{
    // https://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/transformation_review.pdf
    class Transform
    {
    public:
        Transform Inverse();
        bool IsAffine2DTransform();
        void Reset();
        Transform Clone();
        Transform Rotate(float angle);
        Transform Scale(float scaleX, float scaleY);
        Transform Scale(const Vector2& scale);
        // Applies a shear factor (skew) to the Transform's coordinate system.
        // https://en.wikipedia.org/wiki/Shear_mapping
        Transform Shear(float shearX, float shearY);
        Transform Shear(const Vector2& shear);
        Transform Translate(float translateX, float translateY);
        Transform Translate(const Vector2& translation);
        // Applies the Transform object's transformation to the given 2D position
        // This effectively converts the given position from global coordinates into the local coordinate space of the Transform
        Vector2 TransformPoint(const Vector2& global);
        // Applies the reverse of the Transform object's transformation to the given 2D position.
        // This effectively converts the given position from the local coordinate space of the Transform into global coordinates.
        // One use of this method can be to convert a screen-space mouse position into global world coordinates,
        // if the given Transform has transformations applied that are used for a camera system in-game
        Vector2 InverseTransformPoint(const Vector2& local);

    };
}