
#ifndef H_GL_RENDERER_DISPATCHER
#define H_GL_RENDERER_DISPATCHER

#include "public/stl.h"
#include "graphics/renderer/gl_renderer.h"

class gl_renderer_dispatcher {
public:

    gl_renderer_dispatcher() = default;

private:

    std::unordered_map<std::string, std::shared_ptr<gl_renderer>> _renderers_map;

public:

    void add_renderer(std::shared_ptr<gl_renderer> renderer)
    {
        if(renderer)
        {
        }
    }

    void tick(std::float_t delta_time)
    {
        for(auto& _renderer : _renderers_map)
        {
            _renderer.second->render(delta_time);
        }
    }

};


#endif
