#pragma once

#include <Vector2.hpp>

namespace ReBackyardMonsters
{
    struct Rectangle
    {
        // Returns the X coordinate of the left edge
        float GetLeft();
        // Returns the X coordinate of the right edge
        float GetRight();
        // Returns the Y coordinate of the top edge
        float GetTop();
        // Returns the Y coordinate of the bottom edge
        float GetBottom();
        Vector2 GetTopRight();
        Vector2 GetTopLeft();
        Vector2 GetBottomLeft();
        Vector2 GetBottomRight();
        Vector2 GetCenter();
        bool Contains(Vector2);
        bool Contains(Rectangle);
        bool Intersects(Rectangle);
        // Creates a Rectangle out of the overlapping region of two other rectangles
        Rectangle GetIntersectionWith(Rectangle other);
    };
}
