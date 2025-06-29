#pragma once


#include <cmath>
#include <iostream>



class vec3
{
public:
    double e[3];

public:
    vec3();
    vec3(double x, double y,double z);

    double GetX() const;
    double GetY() const;
    double GetZ() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);


    vec3& operator+=(const vec3& v);
    vec3& operator-=(const vec3& v);
    vec3& operator*=(const double t);
    vec3& operator/=(const double t);
    
    double length() const;
    double length_squared() const;
    
    static vec3 random();
    static vec3 random(double min , double max);
    static vec3 random_in_unit_disk();
    bool near_zero() const;
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_unit_vector()
{
    while(true)
    {
        auto p = vec3::random(-1,1);
        auto len = p.length_squared();
        if ( 1e-160 < len && len <= 1 )
            return p / sqrt(len);
    }
}

inline vec3 random_on_hemisphere(const vec3& normal)
{
    vec3 temp = random_unit_vector();
    if (dot(temp, normal) > 0.0)
        return temp;
    else
        return -temp;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat)
{
    auto cons_theta = std::fmin(dot(-uv,n),1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cons_theta * n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}