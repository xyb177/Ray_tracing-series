#pragma once

#include "vec3.h"

class ray
{
public:
    ray();
    ray(const point3& origin, const vec3& direction,double time);
    ray(const point3& origin, const vec3& direction);
    const point3 GetOrigin() const;
    const vec3 GetDirection() const;
    point3 at(double t)  const;  
    double time() const;
private:
    point3 orig;
    vec3 dir;
    double tm;
    
};