// Collision Solver C++ Version
// Ported from CaveGame's C# implementation
// @auth Josj
#pragma once

#include <Rectangle.hpp>
#include <Vector2.hpp>

#include <cmath>

namespace ReBackyardMonsters
{
    enum CollisionFace {
        TOP, LEFT, BOTTOM, RIGHT
    };
    struct LineSegment
    {
        Vector2 A;
        Vector2 B;
        Vector2 GetMidpoint() const;
        LineSegment(Vector2 a, Vector2 b) : A(a), B(b) {}
    };

    class CollisionSolver
    {
    public:
        static bool Intersects(LineSegment seg, Rectangle rect, Vector2* outIntersect, CollisionFace* outFace)
        {
            *outIntersect = Vector2::Zero;
            *outFace = TOP;

            Vector2 topleft = Vector2(rect.GetLeft(), rect.GetTop());
            Vector2 bottomright = Vector2(rect.GetRight(), rect.GetBottom());
            Vector2 bottomleft = Vector2(rect.GetLeft(), rect.GetBottom());
            Vector2 topright = Vector2(rect.GetRight(), rect.GetTop());

            LineSegment top = LineSegment(topleft, topright);
            LineSegment left = LineSegment(topleft, bottomleft);
            LineSegment bottom = LineSegment(bottomleft, bottomright);
            LineSegment right = LineSegment(topright, bottomright);

            Vector2 top_intersect;
            bool top_hits = Intersects(seg, top, &top_intersect);
            Vector2 bottom_intersect;
            bool bottom_hits = Intersects(seg, top, &bottom_intersect);
            Vector2 left_intersect;
            bool left_hits = Intersects(seg, top, &left_intersect);
            Vector2 right_intersect;
            bool right_hits = Intersects(seg, top, &right_intersect);

            if (top_hits || bottom_hits || left_hits || right_hits)
            {
                *outIntersect = seg.B;
                if (top_hits && seg.A.Distance(top_intersect) < seg.A.Distance(*outIntersect)) {
                    *outIntersect = top_intersect;
                    *outFace = TOP;
                }
                if (bottom_hits && seg.A.Distance(bottom_intersect) < seg.A.Distance(*outIntersect)) {

                }
            }
        }
        static bool Intersects(LineSegment s1, LineSegment s2, Vector2* intersection) {
            return Intersects(s1.A, s1.B, s2.A, s2.B, intersection);
        }
        static bool Intersects(Vector2 a1, Vector2 a2, Vector2 b1, Vector2 b2, Vector2* intersection)
        {
            *intersection = Vector2::Zero;
            Vector2 b = a2 - a1;
            Vector2 d = b2 - b1;
            float bDotDPerp = b.GetX() * d.GetY() - b.GetY() * d.GetX();

            // Lines are parallel >> infinite intersections
            if (bDotDPerp == 0)
                return false;

            Vector2 c = b1 - a1;
            float t = (c.GetX() * d.GetY() - c.GetY() * d.GetX()) / bDotDPerp;
            if (t < 0 || t > 1)
                return false;

            float u = (c.GetX() * b.GetY() - c.GetY() * b.GetX()) / bDotDPerp;
            if (u < 0 || u > 1)
                return false;

            *intersection = a1 + t * b;
            return true;
        }

        static bool CheckAABB(Vector2 posA, Vector2 sizeA, Vector2 posB, Vector2 sizeB) {
            float absDistX = std::abs(posA.GetX() - posB.GetX());
            float absDistY = std::abs(posA.GetY() - posB.GetY());

            float sumWidth = sizeA.GetX() + sizeB.GetX();
            float sumHeight = sizeA.GetY() + sizeB.GetY();

            if (absDistY >= sumHeight || absDistX >= sumWidth)
                return false;
            return true;
        }

        static Vector2 GetSeparationAABB(Vector2 posA, Vector2 sizeA, Vector2 posB, Vector2 sizeB) {
            float distanceX = posA.GetX() - posB.GetX();
            float distanceY = posA.GetY() - posB.GetY();
            float absDistX = std::abs(distanceX);
            float absDistY = std::abs(distanceY);
            float sumWidth = sizeA.GetX() + sizeB.GetX();
            float sumHeight = sizeA.GetY() + sizeB.GetY();
            float sx = sumWidth - absDistX;
            float sy = sumHeight - absDistY;

            if (sx > sy) {
                if (sy > 0)
                    sx = 0;
            } else {
                if (sx > 0)
                    sy = 0;
            }
            if (distanceX < 0)
                sx = -sx;
            if (distanceY < 0)
                sy = -sy;
            return Vector2(sx, sy);

        }

        static Vector2 GetNormalAABB(Vector2 separation, Vector2 velocity) {
            float d = std::sqrt(separation.GetX()*separation.GetX() + separation.GetY()*separation.GetY());
            float nx = separation.GetX() / d;
            float ny = separation.GetY() / d;
            float ps = velocity.GetX() * nx + velocity.GetY() * ny;
            if (ps <= 0)
                return Vector2(nx, ny);
            return Vector2(0, 0);
        }


    };
}