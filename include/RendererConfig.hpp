#ifndef RENDERERCONFIG_H
#define RENDERERCONFIG_H

struct RendererConfig
{
    int fb_width;
    int fb_height;
    bool vsync;
    int framecap;
    bool compat_profile;
};

#endif // RENDERERCONFIG_H
