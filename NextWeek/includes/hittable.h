#pragma once

#include "ray.h"
#include "interval.h"
#include <memory>  
#include "aabb.h"
#include "rtweekend.h"
class material;


class hit_record
{
public:
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat;
    double t;
    double u;
    double v;
    bool front_face;

    void set_face_normal(const ray&  r ,const vec3& outward_normal)
    {
        front_face = dot(r.GetDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};


class hittable
{
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;

    virtual aabb bounding_box() const = 0;
};

class translate : public hittable
{
public:
    translate(std::shared_ptr<hittable> object,const vec3& offset)
        : object(object),offset(offset)
    {
        bbox = object->bounding_box() + offset;
    }

    bool hit(const ray& r, interval ray_t,hit_record& rec) const override
    {    // Move the ray backwards by the offset
        ray offset_r(r.GetOrigin() - offset, r.GetDirection(),r.time());
        //Determine whether an intersection exists along the offset ray (and if so, where)
        if(!object->hit(offset_r, ray_t,rec))
            return false;
        rec.p += offset;
        return true;
    }

    aabb bounding_box() const override { return bbox; };
private:
    std::shared_ptr<hittable> object;
    vec3 offset;
    aabb bbox;
};

class rotate_y : public hittable
{
public:
    rotate_y(std::shared_ptr<hittable> object, double angle) : object(object)
    {
        auto radians = degrees_to_radians(angle);
        sin_theta = std::sin(radians);
        cos_theta = std::cos(radians);
        bbox = object->bounding_box();

        point3 min( infinity, infinity, infinity);
        point3 max(-infinity, -infinity, -infinity);

        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k =0;k<2;k++)
                {
                    auto x = i * bbox.x.maxn + (1-i) * bbox.x.minn;
                    auto y = j * bbox.y.maxn + (1-j) * bbox.y.minn;
                    auto z = k * bbox.z.maxn + (1-k) * bbox.z.minn;

                    auto newx =  cos_theta*x + sin_theta*z;
                    auto newz = -sin_theta*x + cos_theta*z;
                    
                    vec3 tester(newx, y, newz);

                    for (int c = 0; c < 3; c++) {
                        min[c] = std::fmin(min[c], tester[c]);
                        max[c] = std::fmax(max[c], tester[c]);
                    }
                }
            }
        }
        bbox = aabb(min, max);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override
    {
        auto origin = point3(
            (cos_theta * r.GetOrigin().GetX()) - (sin_theta*r.GetOrigin().GetZ()),
            r.GetOrigin().GetY(),
            (sin_theta * r.GetOrigin().GetX()) + (cos_theta*r.GetOrigin().GetZ())
        );

        auto direction = vec3(
            (cos_theta * r.GetDirection().GetX()) - (sin_theta*r.GetDirection().GetZ()),
            r.GetDirection().GetY(),
            (sin_theta * r.GetDirection().GetX()) + (cos_theta*r.GetDirection().GetZ())
        );

        ray rotate_r(origin,direction,r.time());

        if (!object -> hit(rotate_r,ray_t,rec))
            return false;

        rec.p = point3(
            (cos_theta * rec.p.GetX()) + (sin_theta * rec.p.GetZ()),
            rec.p.GetY(),
            (-sin_theta * rec.p.GetX()) + (cos_theta * rec.p.GetZ())
        );

        rec.normal = vec3(
            (cos_theta * rec.normal.GetX()) + (sin_theta * rec.normal.GetZ()),
            rec.normal.GetY(),
            (-sin_theta * rec.normal.GetX()) + (cos_theta * rec.normal.GetZ())
        );
        return true;
    }

    aabb bounding_box() const override {return bbox;}

private:
    std::shared_ptr<hittable> object;
    double sin_theta;
    double cos_theta;
    aabb bbox;
};