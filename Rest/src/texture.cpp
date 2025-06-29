#pragma once 
#include "texture.h"

solid_color::solid_color(const color& albedo) : albedo(albedo) {}

solid_color::solid_color(double red ,double green, double blue) : solid_color(color(red, green, blue)) {}

color solid_color::value(double u ,double v, const point3& p) const
{
    return albedo;
}

checker_texture::checker_texture(double scale, std::shared_ptr<texture> even, std::shared_ptr<texture> odd) : inv_scale(1.0/scale), even(even), odd(odd) {}

checker_texture::checker_texture(double scale, const color& c1, const color& c2) : checker_texture(scale, std::make_shared<solid_color>(c1), std::make_shared<solid_color>(c2)) {}

color checker_texture::value(double u, double v, const point3& p) const
{
   auto xInteger = int(std::floor(inv_scale * p.GetX()));
   auto yInteger = int(std::floor(inv_scale * p.GetY()));
   auto zInteger = int(std::floor(inv_scale * p.GetZ()));

   bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;
   return isEven ? even->value(u,v,p): odd->value(u,v,p);
}


image_texture::image_texture(const char* filename) : image(filename){}

color image_texture::value(double u ,double v, const point3& p) const
{
    if (image.height() <= 0) return color(0,1,1);

    u = interval(0,1).clamp(u);
    v = 1.0 - interval(0,1).clamp(v);

    auto i = int(u * image.width());
    auto j = int(v * image.height());
    auto pixel = image.pixel_data(i,j);

    auto color_scale = 1.0 /255.0;
    return color(color_scale*pixel[0],color_scale*pixel[1], color_scale* pixel[2]);
}   


noise_texture::noise_texture(double scale):scale(scale){}

color noise_texture::value(double u,double v, const point3& p) const
{
    return color(.5, .5, .5) * (1 + std::sin(scale * p.GetZ() + 10 * noise.turb(p, 7)));
}