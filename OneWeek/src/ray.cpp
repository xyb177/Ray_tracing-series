#pragma once 

#include "ray.h"

ray::ray(){}

ray::ray(const point3& origin, const vec3& direction)
    :orig(origin),dir(direction){}

const vec3 ray::GetDirection() const {
        return dir;
}

const point3 ray::GetOrigin() const {
    return orig;
}

point3 ray::at(double t) const{
    return orig + t*dir;
}