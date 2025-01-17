#ifndef VEC3H
#define VEC3H
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class vec3 {
    public:
        vec3() {}
        vec3(float e0, float e1, float e2) { 
            e[0] = e0;
            e[1] = e1;
            e[2] = e2;
        }

        inline float x() const {return e[0];}
        inline float y() const {return e[1];}
        inline float z() const {return e[2];}
        inline float r() const {return e[0];}
        inline float g() const {return e[1];}
        inline float b() const {return e[2];}

        inline const vec3& operator+() const {return *this;}
        inline vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
        inline float operator[](int i) const {return e[i];}
        inline float& operator[](int i) {return e[i];}

        inline vec3& operator+=(const vec3 &v2);
        inline vec3& operator-=(const vec3 &v2);
        inline vec3& operator*=(const vec3 &v2);
        inline vec3& operator/=(const vec3 &v2);
        inline vec3& operator*=(const float t);
        inline vec3& operator/=(const float t);

        // norma del vettore
        inline float lenght() const {return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);}


        inline float squared_length() const {return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}

        inline void make_unit_vector();

        float e[3];
};

inline istream& operator>>(istream &is, vec3 &t){
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline ostream& operator<<(ostream &os, vec3 &t){
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

// metodi o funzioni globali ?
inline vec3 operator+(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(float t, const vec3 &v1){
    return vec3(t*v1.e[0], t*v1.e[1], t*v1.e[2]);
}

inline vec3 operator/(const vec3 &v1, float t){
    return vec3(v1.e[0]/t, v1.e[1]/t, v1.e[2]/t);
}

// prodotto scalare
inline float dot(const vec3 &v1, const vec3 &v2){
    return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}

// ?
inline vec3 cross(const vec3 &v1, const vec3 &v2){
    return vec3(
        (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
        -(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0]),
        (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0])
    );
}

inline void vec3::make_unit_vector(){
    float k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

// local operators overloading 

inline vec3& vec3::operator+=(const vec3 &v){
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];

    return *this;
}

inline vec3& vec3::operator*=(const vec3 &v){
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];

    return *this;
}

inline vec3& vec3::operator-=(const vec3 &v){
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];

    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v){
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];

    return *this;
}

inline vec3& vec3::operator*=(const float t){
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;

    return *this;
}

inline vec3& vec3::operator/=(const float k){

    float t = 1.0/k;

    e[0] *= t;
    e[1] *= t;
    e[2] *= t;

    return *this;
}

inline vec3 unit_vector(vec3 v){
    return v/v.lenght();
}
#endif