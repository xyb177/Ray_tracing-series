#pragma once 
#include "interval.h"
#include <limits>
const double infinity = std::numeric_limits<double>::infinity();

interval::interval():minn(infinity),maxn(-infinity) {}

interval::interval(double min, double max) : minn(min), maxn(max) {}

interval::interval(const interval& a, const interval& b)
{
    minn = a.minn < b.minn ? a.minn : b.minn;
    maxn = a.maxn > b.maxn ? a.maxn : b.maxn;
}

double interval::size() const
{
    return maxn - minn;
}

bool interval::contains(double x) const
{
    return minn <= x && x <= maxn;
}

bool interval::surrounds(double x) const
{
    return minn < x && x < maxn;
}

double interval::clamp(double x) const
{
    if (x < minn) return minn;
    if (x > maxn) return maxn;
    return x;
}

interval interval::expand(double delta) const
{
    auto padding = delta/2;
    return interval(minn - padding, maxn + padding);
}
const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);