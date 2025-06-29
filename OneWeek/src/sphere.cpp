#pragma once
#include "sphere.h"

sphere::sphere(const point3& center, double radius,std::shared_ptr<material> mat)
    :center(center),radius(std::fmax(0,radius)), mat(mat){}

bool sphere::hit(const ray& r,interval ray_t, hit_record& rec)const 
{
    vec3 oc = center - r.GetOrigin();
    auto a = r.GetDirection().length_squared();
    auto h = dot(r.GetDirection(), oc);
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = h*h - a*c;
    if (discriminant < 0)
        return false;

    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)) 
    {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    
    rec.normal = (rec.p - center) / radius;
    rec.set_face_normal(r, rec.normal);
    rec.mat = mat;
    return true;
}