
#ifndef H_GL_STATIC_MESH_RENDERER
#define H_GL_STATIC_MESH_RENDERER
#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)
    
    IMPLEMENTATION_FUNC_BUILD()
    {
        gl_graphics_pipeline_descriptor _desc;
        _desc.vertex_processing.vertex_shading.shader;
        builder.create_graphics_pipeline(_desc);
        if (true)
        {

    }

    IMPLEMENTATION_FUNC_RENDER()
    {
        
    }

public:

    void calculate(); 


DEFINE_RENDERER_END()

#endif
