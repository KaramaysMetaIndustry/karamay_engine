#include "gl_graphics_pipeline.h"

void gl_graphics_pipeline::install()
{

    // Stencil test
    {

        enum gl_stencil_func : GLenum
        {
            never = GL_NEVER,
            always = GL_ALWAYS,
            less = GL_LESS,
            less_equal = GL_LEQUAL,
            greater = GL_GREATER,
            greater_equal = GL_GEQUAL,
            equal = GL_EQUAL,
            not_equeal = GL_NOTEQUAL
        };

        gl_stencil_func _stencil_func;
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(static_cast<GLenum>(_stencil_func), 0, 1);
        glStencilFuncSeparate(static_cast<GLenum>(_stencil_func), static_cast<GLenum>(_stencil_func), 0, 1);
        
        enum gl_stencil_op : GLenum
        {
            keep = GL_KEEP,
            zero = GL_ZERO,
            replace = GL_REPLACE,
            incr = GL_INCR,
            incr_wrap = GL_INCR_WRAP,
            decr = GL_DECR,
            decr_wrap = GL_DECR_WRAP,
            invert = GL_INVERT
        };
        glStencilOp();
        glStencilOpSeparate();
        glStencilMask();
        glStencilMaskSeparate();
    }

    // Depth test
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_CLAMP);
        glDepthFunc();
        glDepthRange();
    }

    // blend
    {
        glEnable(GL_BLEND);
        glBlendFunc();
        glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
        glBlendFuncSeparate();
    }

    //Dithering
    {

    }

    // color logic operations
    {
        enum class gl_logic_op : GLenum
        {
            clear = GL_CLEAR,
            set = GL_SET,
            copy = GL_COPY,
            copy_inverted = GL_COPY_INVERTED,
            noop = GL_NOOP,
            invert = GL_INVERT,
            and = GL_AND,
            nand = GL_NAND,
            or = GL_OR,
            nor = GL_NOR,
            xor = GL_XOR,
            equiv = GL_EQUIV,
            and_reverse = GL_AND_REVERSE,
            and_inverted = GL_AND_INVERTED,
            or_reverse = GL_OR_REVERSE,
            or_inverted = GL_OR_INVERTED
        };

        gl_logic_op _logic_op;
        glEnable(GL_COLOR_LOGIC_OP);
        glDisable(GL_COLOR_LOGIC_OP);
        glLogicOp(static_cast<GLenum>(_logic_op));
    }

    // additional multisample fragment operations
    {

    }

    
    

    glEnable(GL_CLIP_DISTANCE0);

    

    

    glEnable(GL_DITHER);

    glEnable(GL_FRAMEBUFFER_SRGB);

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(100);

    glEnable(GL_MULTISAMPLE);
    glSampleCoverage();

    glEnable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glEnable(GL_POLYGON_OFFSET_POINT);
    glEnable(GL_POLYGON_SMOOTH);
    glPolygonOffset();
    glPolygonMode();
    glPolygonOffsetClamp();


    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex();
    glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);

    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    glEnable(GL_SAMPLE_ALPHA_TO_ONE);
    glEnable(GL_SAMPLE_COVERAGE);
    glSampleCoverage();
    glEnable(GL_SAMPLE_SHADING);
    glMinSampleShading();
    glEnable(GL_SAMPLE_MASK);
    glSampleMaski();
    glEnable(GL_SCISSOR_TEST);
    glScissor();
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    glEnable(GL_PROGRAM_POINT_SIZE);

    

    // 到达光栅化之前抛弃所有图元, 使得光栅化包括光栅化之后的阶段全部失效
    if (_descriptor.stage_rasterization.reject_rasterization)  
        glEnable(GL_RASTERIZER_DISCARD); 
    else
        glDisable(GL_RASTERIZER_DISCARD);

    /*glEnable(GL_CULL_FACE);
    glCullFace(GL_CCW);*/

    
}

void gl_graphics_pipeline::draw_rectangles()
{
}

void gl_graphics_pipeline::draw_triangles()
{
}

void gl_graphics_pipeline::draw_triangle_strips()
{
}

void gl_graphics_pipeline::_initialize_graphics_pipeline()
{
}

void gl_graphics_pipeline::_compile_pipeline()
{
}
