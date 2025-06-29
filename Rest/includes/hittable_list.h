#pragma once

#include <memory>
#include <vector>
#include "hittable.h"
#include "aabb.h"

using std::make_shared;
using std::shared_ptr;

class hittable_list: public hittable
{
public:
    std::vector<shared_ptr<hittable>> objects;

public:
    hittable_list();
    hittable_list(shared_ptr<hittable> object);

    void clear();
    void add(shared_ptr<hittable> object);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const  override;
    aabb bounding_box() const override;
private:
    aabb bbox;
};        