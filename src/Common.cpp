#include <vector>
#include <fmt/core.h>

struct RGBAC
{
    float r, g, b, a;
};

template <typename Vec3Type>
struct Vec3
{
    Vec3Type x;
    Vec3Type y;
    Vec3Type z;
};

template <typename Vec2Type>
struct Vec2
{
    Vec2Type x;
    Vec2Type y;
};

using Position = Vec3<int>;
using Rotation = Vec3<int>;
using Scale = Vec3<float>;

using WireMesh = std::vector<Position>; // A wireframe mesh consisting of only vertices. persumed to be rendered using GL_LINES

struct WindowConfig
{
    char window_title[128];
    bool window_borders;
    bool resizable;
};

struct RendererConfig
{
    int fb_width;
    int fb_height;

    bool vsync;
    int framecap;
    bool compat_profile;
};

struct Face
{
    std::vector<Position> vertices;
    RGBAC color;
};