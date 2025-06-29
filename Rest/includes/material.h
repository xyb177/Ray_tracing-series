#pragma once

#include "hittable.h"
#include "color.h"
#include "texture.h"

class material
{
public:
    virtual ~material() = default;

    virtual color emitted(double u,double v, const point3& p) const{
        return color(0,0,0);
    }

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,ray& scattered) const
    {
        return false;
    }
};

class lambertian : public material {
    public:
      lambertian(const color& albedo);
      lambertian(std::shared_ptr<texture> tex); 

      bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
  
    private:
      std::shared_ptr<texture> tex;
};


class metal:public material{
public:
    metal(const color& albedo, double fuzz);
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
private:
    color albedo;
    double fuzz;
};


class dielectric : public material{
public:
    dielectric(double refraction_index);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

private:
    double refraction_index;
    static double reflectance(double cosine, double refraction_index);
};

class diffuse_light : public material{
public:
    diffuse_light(std::shared_ptr<texture> tex);
    diffuse_light(const color& emit);

    color emitted(double u ,double v ,const point3& p) const override;

private:
    shared_ptr<texture> tex;

};


class isotropic: public material{
public:
    isotropic(const color& albedo);
    isotropic(std::shared_ptr<texture> tex);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

private:
    std::shared_ptr<texture> tex;
};