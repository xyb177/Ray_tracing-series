#pragma once
#include "aabb.h"

aabb::aabb(){}

aabb::aabb(const interval& x, const interval& y, const interval& z) : x(x), y(y), z(z) {}

aabb::aabb(const point3& a, const point3& b)
{
    x = ( a[0] <= b[0] ) ? interval(a[0], b[0]) : interval(b[0], a[0]);
    y = ( a[1] <= b[1] ) ? interval(a[1], b[1]) : interval(b[1], a[1]);
    z = ( a[2] <= b[2] ) ? interval(a[2], b[2]) : interval(b[2], a[2]);
}

aabb::aabb(const aabb& box0, const aabb& box1)
{
    x = interval(box0.x, box1.x);
    y = interval(box0.y, box1.y);
    z = interval(box0.z, box1.z);
}

const interval& aabb::axis_interval(int n) const
{
    if (n == 1) return y;
    if (n == 2) return z;
    return x;
}

bool aabb::hit(const ray& r, interval ray_t) const
{   
    const point3& ray_orig = r.GetOrigin();
    const vec3& ray_dir = r.GetDirection();
    for (int i = 0; i < 3; i++) {
       const interval& ax = axis_interval(i);
       const double adinv = 1.0 / ray_dir[i];

       auto t0 = (ax.minn - ray_orig[i]) * adinv;
       auto t1 = (ax.maxn - ray_orig[i]) * adinv;

       if (t0 < t1)
       {
            if (t0 > ray_t.minn) ray_t.minn = t0;
            if (t1 < ray_t.maxn) ray_t.maxn = t1;
       } 
       else
       {
            if (t1 > ray_t.minn) ray_t.minn = t1;
            if (t0 < ray_t.maxn) ray_t.maxn = t0;
       }

       if (ray_t.maxn <= ray_t.minn) return false;
    }
    return true;
}

int aabb::longest_axis() const
{
    if (x.size() > y.size()) 
        return x.size() > z.size() ? 0:2;
    else
        return y.size() > z.size() ? 1:2;    
}

void aabb::pad_to_minimums()
{
    double delta = 0.0001;
    if(x.size() < delta) x = x.expand(delta);
    if(y.size() < delta) y = y.expand(delta);
    if(z.size() < delta) z = z.expand(delta);
}

const aabb aabb::empty    = aabb(interval::empty,    interval::empty,    interval::empty);
const aabb aabb::universe = aabb(interval::universe, interval::universe, interval::universe);