#pragma once

#include "perlin.h"

perlin::perlin()
{
    for (int i=0;i<point_count;i++)
    {
        randvec[i] = unit_vector(vec3::random(-1,1));
    }

    perlin_generate_perm(perm_x);
    perlin_generate_perm(perm_y);
    perlin_generate_perm(perm_z);
}

double perlin::noise(const point3& p) const
{
    auto u = p.GetX() - std::floor(p.GetX());
    auto v = p.GetY() - std::floor(p.GetY());
    auto w = p.GetZ() - std::floor(p.GetZ());

    auto i = int(std::floor(p.GetX()));
    auto j = int(std::floor(p.GetY()));
    auto k = int(std::floor(p.GetZ()));
    vec3 c[2][2][2];

    for(int di = 0;di<2;di++)
        for(int dj = 0;dj < 2;dj++)
            for(int dk = 0; dk<2;dk++)
            c[di][dj][dk] = randvec[
                perm_x[(i + di) &255] ^
                perm_y[(j + dj) &255] ^
                perm_z[(k + dk) &255] 
            ];
    
    return perlin_interp(c,u,v,w);
}

double perlin::turb(const point3 &p, int depth) const
{
    auto accum = 0.0;
    auto temp_p = p;
    auto weight = 1.0;

    for(int i=0;i<depth;i++)
    {
        accum += weight * noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return std::fabs(accum);
}

void perlin::perlin_generate_perm(int* p)
{
    for(int i=0;i<point_count;i++)
        p[i] = i;
    
    permute(p,point_count);
}

void perlin::permute(int*p , int n)
{
    for(int i=n-1;i>0;i--)
    {
        int target = random_int(0,i);
        int temp = p[i];
        p[i] = p[target];
        p[target] = temp;
    }
}

// double perlin::trilinear_interp(double c[2][2][2],double u,double v,double w)
// {
//     auto accum = 0.0;
//     for (int i=0;i<2;i++)
//         for(int j=0;j<2;j++)
//          for(int k =0;k<2;k++)
//            accum += (i*u + (1-i)*(1-u))
//                        * (j*v + (1-j)*(1-v))
//                        * (k*w + (1-k)*(1-w))
//                        * c[i][j][k];
//     return accum;
// }

double perlin::perlin_interp(const vec3 c[2][2][2],double u,double v,double w)
{
    auto uu = u*u*(3-2*u);
    auto vv = v*v*(3-2*v);
    auto ww = w*w*(3-2*w);
    auto accum = 0.0;

    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k =0;k<2;k++)
            {
                vec3 weight_v(u-i, v-j, w-k);
                    accum += (i*uu + (1-i)*(1-uu))
                           * (j*vv + (1-j)*(1-vv))
                           * (k*ww + (1-k)*(1-ww))
                           * dot(c[i][j][k], weight_v);
                
            }
    return accum;
}

