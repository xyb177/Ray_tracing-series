#pragma once

class interval
{

public:
    interval();

    interval(double min, double max);

    interval(const interval& a, const interval& b);

    double size() const;

    bool contains(double x) const;

    bool surrounds(double x) const;

    double clamp(double x) const;

    interval expand(double delta) const;
public:
    double minn,maxn;
    static const interval empty, universe;
};

inline interval operator+(const interval& ival, double displacement) {
    return interval(ival.minn + displacement, ival.maxn + displacement);
}

inline interval operator+(double displacement, const interval& ival) {
    return ival + displacement;
}