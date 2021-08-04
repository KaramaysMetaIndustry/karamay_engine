#include "gl_graphics_pipeline.h"

void gl_graphics_pipeline::_initialize_graphics_pipeline()
{
    // pre-compile pipeline, check conditions
    bool pipeline_validation = false;
    bool pipeline_exist_on_disk = false;
    std::vector<std::string> shader_paths;
    if (_descriptor.vertex_processing.vertex_shading.enabled &&
        _descriptor.vertex_processing.tessellation.enabled &&
        _descriptor.vertex_processing.geometry_shading.enabled &&
        _descriptor.fragment_processing.fragment_shading.enabled
        )
    {
        pipeline_validation = true;
    }
    else if (
        true
        )
    {

    }

#ifdef _RELEASE
    if (!pipeline_validation) return;
#endif // 
#ifdef _DEBUG
    if (!pipeline_validation) throw std::exception("pipeline descriptor is invalidate");
#endif // _DEBUG

    std::filesystem::path renderer_path;
    std::filesystem::create_directory(renderer_path.string() + "_pipelines");
    std::ifstream pipeline_file("");
    
    
    
    // generate shader templates
    // create shader strings
    // add input/output attributes
    // add parameter refs
    // add some other specifier
    // create shader files
    

    // compile shader templates, link program
    // collect shaders


    _program = std::make_shared<gl_program>();
    if (_program)
    {
        _program->construct(shader_paths);
    }
}

void gl_graphics_pipeline::_install()
{

    // vertex specification
    {
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0);
        // or
        glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);// 2^N - 1
    }

    // vertex process
    {
        //shading

        // flatshading
        glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

        // clipping
        glEnable(GL_CLIP_DISTANCE0); // [0, GL_MAX_CLIP_DISTANCES-1]
        glClipControl(GL_LOWER_LEFT, GL_NEGATIVE_ONE_TO_ONE);
        // glEnable(GL_DEPTH_CLAMP);
        glDepthRange(1.0l, 1.1l);
        //glDepthRangeArrayv();
        //glDepthRangef();
        glViewport();
        glDepthRangeIndexed();
        glViewportArrayv();
        glViewportIndexedf();
        glViewportIndexedfv();


    }

    // primitive assmebly
    {

    }
    // rasterization
    {
        // 到达光栅化之前抛弃所有图元, 使得光栅化包括光栅化之后的阶段全部失效
        if (true)
            glEnable(GL_RASTERIZER_DISCARD);
        else
            glDisable(GL_RASTERIZER_DISCARD);

        // multisampling
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_SAMPLE_SHADING);
        glMinSampleShading();
        glGetMultisamplefv();

        // points
        glEnable(GL_PROGRAM_POINT_SIZE);
        glDisable(GL_PROGRAM_POINT_SIZE);
        glPointSize(0);
        glPointParameteri();
        glPointParameteriv();
        glPointParameterf();
        glPointParameterfv();

        // line segments
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(1.0f);

        // polygons
        glEnable(GL_POLYGON_SMOOTH);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_FRONT_AND_BACK);

        // polygon rast & depth offset
        glEnable(GL_POLYGON_OFFSET_FILL);
        glEnable(GL_POLYGON_OFFSET_LINE);
        glEnable(GL_POLYGON_OFFSET_POINT);
        glEnable(GL_POLYGON_SMOOTH);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glPolygonOffsetClamp();
        glPolygonOffset(1.2f, 0);

    }

    // pre frag operations
    {

        // scissor test
        glEnable(GL_SCISSOR_TEST);
        glDisable(GL_SCISSOR_TEST);

        glEnablei(GL_SCISSOR_TEST, 0);
        glDisablei(GL_SCISSOR_TEST, 0);
        glScissor(0, 0, 0, 0);
        glScissorArrayv(0, 100, nullptr);
        glScissorIndexed();
        glScissorIndexedv();

        // multisample fragment ops

    }

    // fragment shading
    {

    }

    glEnable(GL_SAMPLE_COVERAGE);

    // alpha to coverage
    {
        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        glEnable(GL_SAMPLE_ALPHA_TO_ONE); // or
    }
    // Stencil test
    {
        // do stencil test and update the stencil buffer
        glEnable(GL_STENCIL_TEST);
        gl_stencil_func _stencil_func;
        glStencilFunc(_stencil_func, 0, 1); // set front-face and back-face function and
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
        glDepthFunc(df_never);
    }
    // occlusion queries
    {

    }
    // blending
    {
        glEnable(GL_BLEND);
        glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
        glBlendFunc();
        glBlendFuncSeparate();
        glBlendFunci();
        glBlendFuncSeparatei();
        glBlendEquation();
        glBlendEquationi();
        glBlendEquationSeparate();
        glBlendEquationSeparatei();
    }
    // sRGB Conversion
    {
        glEnable(GL_FRAMEBUFFER_SRGB);

    }
    //Dithering
    {
        glEnable(GL_DITHER);
    }
    // color logic operations
    {

        gl_logic_op _logic_op;
        glEnable(GL_COLOR_LOGIC_OP);
        glDisable(GL_COLOR_LOGIC_OP);
        glLogicOp(static_cast<GLenum>(_logic_op));
    }
    // additional multisample fragment operations
    {
        glEnable(GL_MULTISAMPLE);
        glSampleCoverage();
    }

    glEnable(GL_SAMPLE_MASK);
    glSampleMaski();

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

}


