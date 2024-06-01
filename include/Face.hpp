#ifndef FACE_H
#define FACE_H

#include <array>
#include "Vec3.hpp"
#include "RGBAC.hpp"

struct Face
{
    std::vector<Position> vertices;
    RGBAC color;
};

#endif // FACE_H
