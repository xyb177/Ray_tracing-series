#pragma once

#include "hittable.h"
#include "hittable_list.h"

class quad : public hittable
{
public:
    quad(const point3& Q, const vec3& u, const vec3& v ,std::shared_ptr<material> mat);

    virtual void set_bounding_box();
    aabb bounding_box() const override ;

    bool hit(const ray& r ,interval ray_t, hit_record& rec) const override;
    virtual bool is_interior(double a ,double b ,hit_record& rec) const;

private:
    point3 Q;
    vec3 u,v;
    vec3 w;

    std::shared_ptr<material> mat;
    aabb bbox;
    vec3 normal;
    double D;
};

inline std::shared_ptr<hittable_list> box(const point3& a,const point3& b, std::shared_ptr<material>mat)
{
    auto sides = std::make_shared<hittable_list>();

    auto min = point3(std::fmin(a.GetX(),b.GetX()),std::fmin(a.GetY(),b.GetY()),std::fmin(a.GetZ(),b.GetZ()));
    auto max = point3(std::fmax(a.GetX(),b.GetX()),std::fmax(a.GetY(),b.GetY()),std::fmax(a.GetZ(),b.GetZ()));

    auto dx = vec3(max.GetX() - min.GetX(),0,0);
    auto dy = vec3(0,max.GetY() - min.GetY(),0);
    auto dz = vec3(0,0,max.GetZ() - min.GetZ());

    sides->add(make_shared<quad>(point3(min.GetX(), min.GetY(), max.GetZ()),  dx,  dy, mat)); // front
    sides->add(make_shared<quad>(point3(max.GetX(), min.GetY(), max.GetZ()), -dz,  dy, mat)); // right
    sides->add(make_shared<quad>(point3(max.GetX(), min.GetY(), min.GetZ()), -dx,  dy, mat)); // back
    sides->add(make_shared<quad>(point3(min.GetX(), min.GetY(), min.GetZ()),  dz,  dy, mat)); // left
    sides->add(make_shared<quad>(point3(min.GetX(), max.GetY(), max.GetZ()),  dx, -dz, mat)); // top
    sides->add(make_shared<quad>(point3(min.GetX(), min.GetY(), min.GetZ()),  dx,  dz, mat)); // bottom

    return sides;
}