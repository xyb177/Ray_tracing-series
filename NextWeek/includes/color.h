#pragma once

#include "vec3.h"
#include <iostream>
#include "interval.h"

using color = vec3;
void write_color(std::ostream& out, const color& pixel_color);

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}