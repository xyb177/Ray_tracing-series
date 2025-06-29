#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    //Stationary Sphere
    sphere(const point3& static_center, double radius,std::shared_ptr<material> mat);
    // Moving Sphere
    sphere(const point3& center1, const point3& center2, double radius, std::shared_ptr<material> mat);
    
    bool hit(const ray& r, interval ray_t,hit_record& rec) const override;
    aabb bounding_box() const override;
    
private:
    ray center;
    double radius;
    std::shared_ptr<material> mat;
    aabb bbox;
    static void get_sphere_uv(const point3& p, double& u ,double& v);
};