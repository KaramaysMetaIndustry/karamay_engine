
#ifndef H_GL_RENDERER_DISPATCHER
#define H_GL_RENDERER_DISPATCHER

#include "public/stl.h"

class gl_renderer;

class gl_renderer_dispatcher {
public:

    gl_renderer_dispatcher() = default;

private:

    std::unordered_map<std::string, std::shared_ptr<gl_renderer>> _renderers_map;

public:

    void tick(std::float_t delta_time)
    {
    }

};


#endif
