#include "PointOperations.h"

std::vector<sPoint> PointOperations::transformToPoints(const std::vector<int>& aX, const std::vector<int>& aY)
{
    int n = aX.size();
    std::vector<sPoint> points(n);
    for (int i = 0; i < n; ++i) {
        points[i] = { aX[i], aY[i] };
    }
    return points;
}

std::vector<sPoint> PointOperations::generateRandomPoints(int aN, int aMinValue/*= -100*/, int aMaxValue/*= 100*/)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(aMinValue, aMaxValue);

    std::vector<sPoint> points;
    points.reserve(aN);
    for (int i = 0; i < aN; ++i) {
        points.push_back({ dis(gen), dis(gen) });
    }
    return points;
}

float PointOperations::stripClosest(const std::vector<sPoint>& aStrip, float aD, sPoint& aClosest1, sPoint& aClosest2)
{
    float minDist = aD;
    int n = aStrip.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n && (aStrip[j].y - aStrip[i].y) < minDist; ++j)
        {
            float dist = aStrip[i].distanceTo(aStrip[j]);
            if (dist < minDist) {
                minDist = dist;
                aClosest1 = aStrip[i];
                aClosest2 = aStrip[j];
            }
        }
    }
    return minDist;
}

float PointOperations::closestUtil(std::vector<sPoint>& aPoints, int aLeft, int aRight, sPoint& aClosest1, sPoint& aClosest2, int aDepth/*= 0*/)
{
    if (aRight - aLeft <= 3)
    {
        float minDist = std::numeric_limits<float>::max();
        for (int i = aLeft; i < aRight; ++i)
        {
            for (int j = i + 1; j < aRight; ++j)
            {
                float dist = aPoints[i].distanceTo(aPoints[j]);
                if (dist < minDist)
                {
                    minDist = dist;
                    aClosest1 = aPoints[i];
                    aClosest2 = aPoints[j];
                }
            }
        }
        return minDist;
    }

    int mid = aLeft + (aRight - aLeft) / 2;
    sPoint midPoint = aPoints[mid];

    sPoint leftClosest1, leftClosest2, rightClosest1, rightClosest2;
    float dl, dr;

    if (aDepth < 2)
    {
        std::future<float> leftFuture = std::async(std::launch::async, closestUtil, std::ref(aPoints), aLeft, mid, std::ref(leftClosest1), std::ref(leftClosest2), aDepth + 1);
        dr = closestUtil(aPoints, mid, aRight, rightClosest1, rightClosest2, aDepth + 1);
        dl = leftFuture.get();
    }
    else
    {
        dl = closestUtil(aPoints, aLeft, mid, leftClosest1, leftClosest2, aDepth + 1);
        dr = closestUtil(aPoints, mid, aRight, rightClosest1, rightClosest2, aDepth + 1);
    }

    float d;
    if (dl < dr)
    {
        d = dl;
        aClosest1 = leftClosest1;
        aClosest2 = leftClosest2;
    }
    else
    {
        d = dr;
        aClosest1 = rightClosest1;
        aClosest2 = rightClosest2;
    }

    std::vector<sPoint> strip;
    for (int i = aLeft; i < aRight; ++i)
    {
        if (std::abs(aPoints[i].x - midPoint.x) < d)
        {
            strip.push_back(aPoints[i]);
        }
    }

    std::sort(strip.begin(), strip.end(), sPoint::compareByY);
    return stripClosest(strip, d, aClosest1, aClosest2);
}

std::pair<sPoint, sPoint> PointOperations::closestPair(std::vector<sPoint>& aPoints)
{
    std::sort(aPoints.begin(), aPoints.end(), sPoint::compareByX);
    sPoint closest1, closest2;
    closestUtil(aPoints, 0, aPoints.size(), closest1, closest2);
    return { closest1, closest2 };
}

float PointOperations::closestDistance(std::vector<sPoint>& aPoints)
{
    auto closest = closestPair(aPoints);
    return closest.first.distanceTo(closest.second);
}

float PointOperations::closestDistance(std::vector<int>& aX, std::vector<int>& aY)
{
    std::vector<sPoint> points = transformToPoints(aX, aY);
    return closestDistance(points);
}