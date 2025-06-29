#pragma once 

#include "ray.h"

ray::ray(){}

ray::ray(const point3& origin, const vec3& direction)
    :orig(origin),dir(direction),tm(0){}
ray::ray(const point3& origin, const vec3& direction, double time)
    :orig(origin),dir(direction),tm(time){}
const vec3 ray::GetDirection() const {
        return dir;
}

const point3 ray::GetOrigin() const {
    return orig;
}

point3 ray::at(double t) const{
    return orig + t*dir;
}

double ray::time() const {
    return tm;
}