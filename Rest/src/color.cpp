#pragma once

#include "color.h"



void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.GetX();
    auto g = pixel_color.GetY();
    auto b = pixel_color.GetZ();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.000,0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));


    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}