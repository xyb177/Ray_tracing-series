#pragma once
#include "hittable_list.h"

using std::make_shared;
using std::shared_ptr;

hittable_list::hittable_list(){
    
}

hittable_list::hittable_list(shared_ptr<hittable> object)
{
    add(object);
}


void hittable_list::clear() 
{
    objects.clear();
}

void hittable_list::add(shared_ptr<hittable> object)
{
    objects.push_back(object);
    bbox = aabb(bbox, object->bounding_box());
}

bool hittable_list::hit(const ray& r, interval ray_t, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_t.maxn;

    for (const auto& object : objects) {
        if (object->hit(r, interval(ray_t.minn, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

aabb hittable_list::bounding_box() const
{
    return bbox;
}
