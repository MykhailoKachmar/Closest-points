#ifndef Types_h
#define Types_h

#include <cmath>

// A structure to represent a point
struct sPoint
{
    int x;
    int y;

    // Method to calculate the distance to another point
    float distanceTo(const sPoint& aPoint) const
    {
        long dx = x - aPoint.x;
        long dy = y - aPoint.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Static method to compare points by x coordinate
    static bool compareByX(const sPoint& aPoint1, const sPoint& aPoint2)
    {
        return aPoint1.x < aPoint2.x;
    }

    // Static method to compare points by y coordinate
    static bool compareByY(const sPoint& aPoint1, const sPoint& aPoint2)
    {
        return aPoint1.y < aPoint2.y;
    }
};

#endif // Types_h