#include "gl_graphics_pipeline.h"

void gl_graphics_pipeline::install()
{

    // Stencil test
    {
		// do stencil test and update the stencil buffer
		glEnable(GL_STENCIL_TEST);

        
        gl_stencil_func _stencil_func;
        glStencilFunc(_stencil_func, 0, 1); // set front and back function and
        glStencilFuncSeparate(static_cast<GLenum>(_stencil_func), static_cast<GLenum>(_stencil_func), 0, 1);
        
       

		gl_stencil_op _stencil_op;
		// stencil test fail , stencil stencil test pass but depth test fail, both pass 
       
        glStencilOpSeparate(GL_FRONT, _stencil_op, _stencil_op, _stencil_op);
        glStencilOpSeparate(GL_BACK, _stencil_op, _stencil_op, _stencil_op);
        glStencilOpSeparate(GL_FRONT_AND_BACK, _stencil_op, _stencil_op, _stencil_op);
		//glStencilOp(_stencil_op, _stencil_op, _stencil_op);
        glStencilMaskSeparate(GL_FRONT, 1);
        glStencilMaskSeparate(GL_BACK, 1);
        glStencilMaskSeparate(GL_FRONT_AND_BACK, 1);
		//glStencilMask(1);

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
