#include <iostream>
#include <iomanip>

#include "PointOperations.h"
#include "ProcessTimeCounter.h"

int main()
{
    std::vector<sPoint> points = PointOperations::generateRandomPoints(10);

    ProcessTimeCounter timer;
    timer.Start();
    // Find the closest pair and calculate the shortest distance
    auto closest = PointOperations::closestPair(points);
    std::cout << "Closest points: (x:" << closest.first.x << ",y:" << closest.first.y << ") and (x:" << closest.second.x << ",y:" << closest.second.y << ")\n";
    std::cout << "Shortest distance: " << std::fixed << std::setprecision(3) << closest.first.distanceTo(closest.second) << std::endl;

    std::cout << "Time (ms): " << timer.Stop().count() << std::endl;

    return 0;
}