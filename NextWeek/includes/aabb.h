#pragma once 
#include "interval.h"
#include "ray.h" 
#include "vec3.h"
class aabb
{
public:
    interval x, y, z;
    void pad_to_minimums();
public:
    aabb();

    aabb(const interval& x, const interval& y, const interval& z);
    
    aabb(const point3& x, const point3& y);

    aabb(const aabb& a, const aabb& b);

    const interval& axis_interval(int n)const;

    bool hit(const ray& r, interval ray_t)const;

    int longest_axis() const;

    static const aabb empty;
    static const aabb universe;
};

inline aabb operator+(const aabb& bbox, const vec3& offset) {
    return aabb(bbox.x + offset.GetX(), bbox.y + offset.GetY(), bbox.z + offset.GetZ());
}

inline aabb operator+(const vec3& offset, const aabb& bbox) {
    return bbox + offset;
}