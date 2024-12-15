#ifndef PointOperations_h
#define PointOperations_h

#include <vector>
#include <algorithm>
#include <random>
#include <future>
#include "Types.h"

// Class for performing operations on points
class PointOperations
{
    PointOperations() = delete;
    ~PointOperations() = delete;
public:

    // Function to transform x and y coordinates to points
    static std::vector<sPoint> transformToPoints(const std::vector<int>& aX, const std::vector<int>& aY);

    // Function to generate random points
    static std::vector<sPoint> generateRandomPoints(int aN, int aMinValue = -100, int aMaxValue = 100);

    // Function to find the closest points in a strip
    static float stripClosest(const std::vector<sPoint>& aStrip, float aD, sPoint& aClosest1, sPoint& aClosest2);

    // Recursive function to find the closest pair of points
    static float closestUtil(std::vector<sPoint>& aPoints, int aLeft, int aRight, sPoint& aClosest1, sPoint& aClosest2, int aDepth = 0);

    // Function to find the closest pair of points
    static std::pair<sPoint, sPoint> closestPair(std::vector<sPoint>& aPoints);

    // Function to calculate the closest distance
    static float closestDistance(std::vector<sPoint>& aPoints);

    // Function to calculate the closest distance from x and y coordinates
    static float closestDistance(std::vector<int>& aX, std::vector<int>& aY);
};

#endif // PointOperations_h