#include "constant_medium.h"

constant_medium::constant_medium(shared_ptr<hittable> boundary, double density, shared_ptr<texture> tex)
      : boundary(boundary), neg_inv_density(-1/density),
        phase_function(make_shared<isotropic>(tex))
       {}

constant_medium::constant_medium(shared_ptr<hittable> boundary, double density, const color& albedo)
      : boundary(boundary), neg_inv_density(-1/density),
        phase_function(make_shared<isotropic>(albedo))
    {}

bool constant_medium::hit(const ray& r, interval ray_t, hit_record& rec) const  {
        hit_record rec1, rec2;
        
        //检测光线是否与体积的外边界相交
        if (!boundary->hit(r, interval::universe, rec1))
            return false;
        //检测光线是否离开体积
        if (!boundary->hit(r, interval(rec1.t+0.0001, infinity), rec2))
            return false;

        if (rec1.t < ray_t.minn) rec1.t = ray_t.minn;
        if (rec2.t > ray_t.maxn) rec2.t = ray_t.maxn;

        if (rec1.t >= rec2.t)
            return false;

        if (rec1.t < 0)
            rec1.t = 0;

        //计算光线在体积内的传播距离    
        auto ray_length = r.GetDirection().length();
        auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;

        // 随机决定光线是否在体积内发生散射
        auto hit_distance = neg_inv_density * std::log(random_double());
        if (hit_distance > distance_inside_boundary)
            return false;

        // 计算散射点的位置和属性
        rec.t = rec1.t + hit_distance / ray_length;
        rec.p = r.at(rec.t);

        rec.normal = vec3(1,0,0);  // arbitrary
        rec.front_face = true;     // also arbitrary
        rec.mat = phase_function;

        return true;
    }

aabb constant_medium::bounding_box() const { return boundary->bounding_box(); }