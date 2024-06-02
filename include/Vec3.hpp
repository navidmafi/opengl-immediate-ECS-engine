#ifndef VEC3_H
#define VEC3_H

template <typename T>
struct Vec3
{
    T x;
    T y;
    T z;
};

using Position = Vec3<float>;
using Rotation = Vec3<int>;
using Scale = Vec3<float>;

#endif // VEC3_H
