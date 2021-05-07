#pragma once

#include <math.h>

class vec2
{
public:
    vec2() { x = y = 0.0f; }
    vec2(float nx, float ny) { x = nx; y = ny; }

    void Set(float nx, float ny) { x = nx; y = ny; }

public:
    float x,y;
};

class vec3
{
public:
    vec3() { x = y = z = 0.0f; }
    vec3(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }

    void Set(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }

    vec3 operator+(const vec3& o) const { return vec3( x+o.x, y+o.y, z+o.z ); }
    vec3 operator-(const vec3& o) const { return vec3( x-o.x, y-o.y, z-o.z ); }
    vec3 operator*(const vec3& o) const { return vec3( x*o.x, y*o.y, z*o.z ); }
    vec3 operator/(const vec3& o) const { return vec3( x/o.x, y/o.y, z/o.z ); }

    vec3 operator+(float o) const { return vec3( x+o, y+o, z+o ); }
    vec3 operator-(float o) const { return vec3( x-o, y-o, z-o ); }
    vec3 operator*(float o) const { return vec3( x*o, y*o, z*o ); }
    vec3 operator/(float o) const { return vec3( x/o, y/o, z/o ); }

    vec3& operator+=(float o) { x+=o, y+=o, z+=o; return *this; }
    vec3& operator-=(float o) { x-=o, y-=o, z-=o; return *this; }
    vec3& operator*=(float o) { x*=o, y*=o, z*=o; return *this; }
    vec3& operator/=(float o) { x/=o, y/=o, z/=o; return *this; }

    float Length() const { return sqrtf( x*x + y*y + z*z ); }
    void Normalize() { *this /= Length(); }
    vec3 GetNormalized() const { return *this / Length(); }

    float Dot(const vec3& o) const { return x*o.x + y*o.y + z*o.z; }

    void Clamp(float min, float max)
    {
        if( x < min ) x = min; if( x > max ) x = max;
        if( y < min ) y = min; if( y > max ) y = max;
        if( z < min ) z = min; if( z > max ) z = max;
    }

    static const vec3 Right() { return vec3( 1, 0, 0 ); }
    static const vec3 Up() { return vec3( 0, 1, 0 ); }
    static const vec3 In() { return vec3( 0, 0, 1 ); }

public:
    float x,y,z;
};

inline vec3 operator*(float s, const vec3& v) { return vec3( v.x*s, v.y*s, v.z*s ); }
inline vec3 operator/(float s, const vec3& v) { return vec3( v.x/s, v.y/s, v.z/s ); }

class ray
{
public:
    ray() {}
    ray(const vec3& o, const vec3& d) { origin = o; dir = d; }

    vec3 at(float t) const
    {
        return origin + t*dir;
    }

public:
    vec3 origin;
    vec3 dir;
};

class ivec2
{
public:
    void Set(int nx, int ny) { x = nx; y = ny; }

public:
    int x,y;
};
