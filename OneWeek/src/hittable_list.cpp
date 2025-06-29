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
    lists.clear();
}

void hittable_list::add(shared_ptr<hittable> object)
{
    lists.push_back(object);
}

bool hittable_list::hit(const ray& r, interval ray_t, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_t.maxn;

    for (const auto& object : lists) {
        if (object->hit(r, interval(ray_t.minn, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
