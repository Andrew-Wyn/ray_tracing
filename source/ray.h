#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray{
    public:
        ray() {}
        ray(const vec3 &a, const vec3 &b){A = a; B = b;}
        vec3 origin() const {return A;}
        vec3 direction() const {return B;}

        // p(t)
        /*

        A  is the ray origin and B is the ray direction. 
        The ray parameter t is a real number (float in the code). 
        Plug in a different t and p(t) moves the point along the ray. 
        Add in negative t and you can go anywhere on the 3D line. 
        For positive t, you get only the parts in front of A, 
        and this is what is often called a half-line or ray.

        prende lo spazio affine 

        */
        vec3 point_at_parameter(float t) const {return A + (t*B);}

        vec3 A;
        vec3 B;
};
#endif