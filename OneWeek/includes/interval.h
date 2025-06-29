#pragma once

class interval
{

public:
    interval();

    interval(double min, double max);

    double size() const;

    bool contains(double x) const;

    bool surrounds(double x) const;

    double clamp(double x) const;
public:
    double minn,maxn;
    static const interval empty, universe;
};