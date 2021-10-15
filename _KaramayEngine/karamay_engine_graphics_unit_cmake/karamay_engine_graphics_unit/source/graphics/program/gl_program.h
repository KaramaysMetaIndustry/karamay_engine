#ifndef H_GL_PROGRAM
#define H_GL_PROGRAM

#include "graphics/glo/gl_object.h"
#include "graphics/glsl/glsl_class.h"
#include "graphics/texture/gl_texture.h"
#include "graphics/framebuffer/gl_framebuffer.h"
#include "graphics/framebuffer/gl_default_framebuffer.h"

class gl_shader;
class gl_vertex_array;
class gl_transform_feedback;

enum class gl_transform_feedback_buffer_mode
{
    SEPARATE_ATTRIBS = GL_SEPARATE_ATTRIBS,
    INTERLEAVED = GL_INTERLEAVED_ATTRIBS,
    UNKNOWN
};

enum class gl_primitive_type
{

    UNKNOWN
};

enum class gl_shader_type : GLenum
{
    UNKNOWN = 0,

    VERTEX_SHADER = GL_VERTEX_SHADER,
    TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
    GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER,

    COMPUTE_SHADER = GL_COMPUTE_SHADER
};

enum class gl_program_interface
{
    PROGRAM_INPUT = GL_PROGRAM_INPUT, // vertex input
    PROGRAM_OUTPUT = GL_PROGRAM_OUTPUT, // fragment output
    UNIFORM = GL_UNIFORM, // uniform item
    UNIFORM_BLOCK = GL_UNIFORM_BLOCK, // uniform block
    SHADER_STORAGE_BLOCK = GL_SHADER_STORAGE_BLOCK, // buffer block
    BUFFER_VARIABLE = GL_BUFFER_VARIABLE, //
    TRANSFORM_FEEDBACK_VARYING = GL_TRANSFORM_FEEDBACK_VARYING, // transform feedback varyings
    TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
    ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,

    VERTEX_SUBROUTINE = GL_VERTEX_SUBROUTINE,
    VERTEX_SUBROUTINE_UNIFORM = GL_VERTEX_SUBROUTINE_UNIFORM,
    TESS_CONTROL_SUBROUTINE = GL_TESS_CONTROL_SUBROUTINE,
    TESS_CONTROL_SUBROUTINE_UNIFORM = GL_TESS_CONTROL_SUBROUTINE_UNIFORM,
    TESS_EVALUATION_SUBROUTINE = GL_TESS_EVALUATION_SUBROUTINE,
    TESS_EVALUATION_SUBROUTINE_UNIFORM = GL_TESS_EVALUATION_SUBROUTINE_UNIFORM,
    GEOMETRY_SUBROUTINE = GL_GEOMETRY_SUBROUTINE,
    GEOMETRY_SUBROUTINE_UNIFORM = GL_GEOMETRY_SUBROUTINE_UNIFORM,
    FRAGMENT_SUBROUTINE = GL_FRAGMENT_SUBROUTINE,
    FRAGMENT_SUBROUTINE_UNIFORM = GL_FRAGMENT_SUBROUTINE_UNIFORM,
    COMPUTE_SUBROUTINE = GL_COMPUTE_SUBROUTINE,
    COMPUTE_SUBROUTINE_UNIFORM = GL_COMPUTE_SUBROUTINE_UNIFORM,
};

enum class glsl_type_enum
{
    FLOAT = GL_FLOAT,
    FLOAT_VEC2 = GL_FLOAT_VEC2,
    FLOAT_VEC3 = GL_FLOAT_VEC3,
    FLOAT_VEC4 = GL_FLOAT_VEC4,
    DOUBLE = GL_DOUBLE,
    DOUBLE_VEC2 = GL_DOUBLE_VEC2,
    DOUBLE_VEC3 = GL_DOUBLE_VEC3,
    DOUBLE_VEC4 = GL_DOUBLE_VEC4,
    INT = GL_INT,
    INT_VEC2 = GL_INT_VEC2,
    INT_VEC3 = GL_INT_VEC3,
    INT_VEC4 = GL_INT_VEC4,
    UNSIGNED_INT = GL_UNSIGNED_INT,
    UNSIGNED_INT_VEC2 = GL_UNSIGNED_INT_VEC2,
    UNSIGNED_INT_VEC3 = GL_UNSIGNED_INT_VEC3,
    UNSIGNED_INT_VEC4 = GL_UNSIGNED_INT_VEC4,
    BOOL = GL_BOOL,
    BOOL_VEC2 = GL_BOOL_VEC2,
    BOOL_VEC3 = GL_BOOL_VEC3,
    BOOL_VEC4 = GL_BOOL_VEC4,
    FLOAT_MAT2 = GL_FLOAT_MAT2,
    FLOAT_MAT3 = GL_FLOAT_MAT3,
    FLOAT_MAT4 = GL_FLOAT_MAT4,
    FLOAT_MAT2x3 = GL_FLOAT_MAT2x3,
    FLOAT_MAT2x4 = GL_FLOAT_MAT2x4,
    FLOAT_MAT3x2 = GL_FLOAT_MAT3x2,
    FLOAT_MAT3x4 = GL_FLOAT_MAT3x4,
    FLOAT_MAT4x2 = GL_FLOAT_MAT4x2,
    FLOAT_MAT4x3 = GL_FLOAT_MAT4x3,
    DOUBLE_MAT2 = GL_DOUBLE_MAT2,
    DOUBLE_MAT3 = GL_DOUBLE_MAT3,
    DOUBLE_MAT4 = GL_DOUBLE_MAT4,
    DOUBLE_MAT2x3 = GL_DOUBLE_MAT2x3,
    DOUBLE_MAT2x4 = GL_DOUBLE_MAT2x4,
    DOUBLE_MAT3x2 = GL_DOUBLE_MAT3x2,
    DOUBLE_MAT3x4 = GL_DOUBLE_MAT3x4,
    DOUBLE_MAT4x2 = GL_DOUBLE_MAT4x2,
    DOUBLE_MAT4x3 = GL_DOUBLE_MAT4x3,
    SAMPLER_1D = GL_SAMPLER_1D,
    SAMPLER_2D = GL_SAMPLER_2D,
    SAMPLER_3D = GL_SAMPLER_3D,
    SAMPLER_CUBE = GL_SAMPLER_CUBE,
    SAMPLER_1D_SHADOW = GL_SAMPLER_1D_SHADOW,
    SAMPLER_2D_SHADOW = GL_SAMPLER_2D_SHADOW,
    SAMPLER_1D_ARRAY = GL_SAMPLER_1D_ARRAY,
    SAMPLER_2D_ARRAY = GL_SAMPLER_2D_ARRAY,
    SAMPLER_CUBE_MAP_ARRAY = GL_SAMPLER_CUBE_MAP_ARRAY,
    SAMPLER_1D_ARRAY_SHADOW = GL_SAMPLER_1D_ARRAY_SHADOW,
    SAMPLER_2D_ARRAY_SHADOW = GL_SAMPLER_2D_ARRAY_SHADOW,
    SAMPLER_2D_MULTISAMPLE = GL_SAMPLER_2D_MULTISAMPLE,
    SAMPLER_2D_MULTISAMPLE_ARRAY = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
    SAMPLER_CUBE_SHADOW = GL_SAMPLER_CUBE_SHADOW,
    SAMPLER_CUBE_MAP_ARRAY_SHADOW = GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW,
    SAMPLER_BUFFER = GL_SAMPLER_BUFFER,
    SAMPLER_2D_RECT = GL_SAMPLER_2D_RECT,
    SAMPLER_2D_RECT_SHADOW = GL_SAMPLER_2D_RECT_SHADOW,
    INT_SAMPLER_1D = GL_INT_SAMPLER_1D,
    INT_SAMPLER_2D = GL_INT_SAMPLER_2D,
    INT_SAMPLER_3D = GL_INT_SAMPLER_3D,
    INT_SAMPLER_CUBE = GL_INT_SAMPLER_CUBE,
    INT_SAMPLER_1D_ARRAY = GL_INT_SAMPLER_1D_ARRAY,
    INT_SAMPLER_2D_ARRAY = GL_INT_SAMPLER_2D_ARRAY,
    INT_SAMPLER_CUBE_MAP_ARRAY = GL_INT_SAMPLER_CUBE_MAP_ARRAY,
    INT_SAMPLER_2D_MULTISAMPLE = GL_INT_SAMPLER_2D_MULTISAMPLE,
    INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
    INT_SAMPLER_BUFFER = GL_INT_SAMPLER_BUFFER,
    INT_SAMPLER_2D_RECT = GL_INT_SAMPLER_2D_RECT,
    UNSIGNED_INT_SAMPLER_1D = GL_UNSIGNED_INT_SAMPLER_1D,
    UNSIGNED_INT_SAMPLER_2D = GL_UNSIGNED_INT_SAMPLER_2D,
    UNSIGNED_INT_SAMPLER_3D = GL_UNSIGNED_INT_SAMPLER_3D,
    UNSIGNED_INT_SAMPLER_CUBE = GL_UNSIGNED_INT_SAMPLER_CUBE,
    UNSIGNED_INT_SAMPLER_1D_ARRAY = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
    UNSIGNED_INT_SAMPLER_2D_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
    UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY = GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY,
    UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
    UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
    UNSIGNED_INT_SAMPLER_BUFFER = GL_UNSIGNED_INT_SAMPLER_BUFFER,
    UNSIGNED_INT_SAMPLER_2D_RECT = GL_UNSIGNED_INT_SAMPLER_2D_RECT,
    IMAGE_1D = GL_IMAGE_1D,
    IMAGE_2D = GL_IMAGE_2D,
    IMAGE_3D = GL_IMAGE_3D,
    IMAGE_2D_RECT = GL_IMAGE_2D_RECT,
    IMAGE_CUBE = GL_IMAGE_CUBE,
    IMAGE_BUFFER = GL_IMAGE_BUFFER,
    IMAGE_1D_ARRAY = GL_IMAGE_1D_ARRAY,
    IMAGE_2D_ARRAY = GL_IMAGE_2D_ARRAY,
    IMAGE_CUBE_MAP_ARRAY = GL_IMAGE_CUBE_MAP_ARRAY,
    IMAGE_2D_MULTISAMPLE = GL_IMAGE_2D_MULTISAMPLE,
    IMAGE_2D_MULTISAMPLE_ARRAY = GL_IMAGE_2D_MULTISAMPLE_ARRAY,
    INT_IMAGE_1D = GL_INT_IMAGE_1D,
    INT_IMAGE_2D = GL_INT_IMAGE_2D,
    INT_IMAGE_3D = GL_INT_IMAGE_3D,
    INT_IMAGE_2D_RECT = GL_INT_IMAGE_2D_RECT,
    INT_IMAGE_CUBE = GL_INT_IMAGE_CUBE,
    INT_IMAGE_BUFFER  = GL_INT_IMAGE_BUFFER ,
    INT_IMAGE_1D_ARRAY = GL_INT_IMAGE_1D_ARRAY,
    INT_IMAGE_2D_ARRAY = GL_INT_IMAGE_2D_ARRAY,
    INT_IMAGE_CUBE_MAP_ARRAY = GL_INT_IMAGE_CUBE_MAP_ARRAY,
    INT_IMAGE_2D_MULTISAMPLE = GL_INT_IMAGE_2D_MULTISAMPLE,
    INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
    UNSIGNED_INT_IMAGE_1D = GL_UNSIGNED_INT_IMAGE_1D,
    UNSIGNED_INT_IMAGE_2D = GL_UNSIGNED_INT_IMAGE_2D,
    UNSIGNED_INT_IMAGE_3D = GL_UNSIGNED_INT_IMAGE_3D,
    UNSIGNED_INT_IMAGE_2D_RECT = GL_UNSIGNED_INT_IMAGE_2D_RECT,
    UNSIGNED_INT_IMAGE_CUBE  = GL_UNSIGNED_INT_IMAGE_CUBE ,
    UNSIGNED_INT_IMAGE_BUFFER = GL_UNSIGNED_INT_IMAGE_BUFFER,
    UNSIGNED_INT_IMAGE_1D_ARRAY = GL_UNSIGNED_INT_IMAGE_1D_ARRAY,
    UNSIGNED_INT_IMAGE_2D_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_ARRAY,
    UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY = GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY,
    UNSIGNED_INT_IMAGE_2D_MULTISAMPLE = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,
    UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
    UNSIGNED_INT_ATOMIC_COUNTER = GL_UNSIGNED_INT_ATOMIC_COUNTER
};

enum class gl_uniform_type : GLenum
{
	FLOAT = GL_FLOAT,	//float
	FLOAT_VEC2 = GL_FLOAT_VEC2,	//vec2
	FLOAT_VEC3 = GL_FLOAT_VEC3,	//vec3
	FLOAT_VEC4 = GL_FLOAT_VEC4,	//vec4
	DOUBLE = GL_DOUBLE,	//double
	DOUBLE_VEC2 = GL_DOUBLE_VEC2,	//dvec2
	DOUBLE_VEC3 = GL_DOUBLE_VEC3,	//dvec3
	DOUBLE_VEC4 = GL_DOUBLE_VEC4,	//dvec4
	INT = GL_INT,	//int
	INT_VEC2 = GL_INT_VEC2,	//ivec2
	INT_VEC3 = GL_INT_VEC3,	//ivec3
	INT_VEC4 = GL_INT_VEC4,	//ivec4
	UNSIGNED_INT = GL_UNSIGNED_INT,	//unsigned int
	UNSIGNED_INT_VEC2 = GL_UNSIGNED_INT_VEC2,	//uvec2
	UNSIGNED_INT_VEC3 = GL_UNSIGNED_INT_VEC3,	//uvec3
	UNSIGNED_INT_VEC4 = GL_UNSIGNED_INT_VEC4,	//uvec4
	BOOL = GL_BOOL,	//bool
	BOOL_VEC2 = GL_BOOL_VEC2,	//bvec2
	BOOL_VEC3 = GL_BOOL_VEC3,	//bvec3
	BOOL_VEC4 = GL_BOOL_VEC4,	//bvec4
	FLOAT_MAT2 = GL_FLOAT_MAT2,	//mat2
	FLOAT_MAT3 = GL_FLOAT_MAT3,	//mat3
	FLOAT_MAT4 = GL_FLOAT_MAT4,	// mat4
	FLOAT_MAT2x3 = GL_FLOAT_MAT2x3,	//mat2x3
	FLOAT_MAT2x4 = GL_FLOAT_MAT2x4,	//mat2x4
	FLOAT_MAT3x2 = GL_FLOAT_MAT3x2,	//mat3x2
	FLOAT_MAT3x4 = GL_FLOAT_MAT3x4,	//mat3x4
	FLOAT_MAT4x2 = GL_FLOAT_MAT4x2,	//mat4x2
	FLOAT_MAT4x3 = GL_FLOAT_MAT4x3,	//mat4x3
	DOUBLE_MAT2 = GL_DOUBLE_MAT2,	//dmat2
	DOUBLE_MAT3 = GL_DOUBLE_MAT3,	//dmat3
	DOUBLE_MAT4 = GL_DOUBLE_MAT4,	//dmat4
	DOUBLE_MAT2x3 = GL_DOUBLE_MAT2x3,	//dmat2x3
	DOUBLE_MAT2x4 = GL_DOUBLE_MAT2x4,	//dmat2x4
	DOUBLE_MAT3x2 = GL_DOUBLE_MAT3x2,	//dmat3x2
	DOUBLE_MAT3x4 = GL_DOUBLE_MAT3x4,	//dmat3x4
	DOUBLE_MAT4x2 = GL_DOUBLE_MAT4x2,	//dmat4x2
	DOUBLE_MAT4x3 = GL_DOUBLE_MAT4x3,	//dmat4x3
	SAMPLER_1D = GL_SAMPLER_1D,	//sampler1D
	SAMPLER_2D = GL_SAMPLER_2D,	//sampler2D
	SAMPLER_3D = GL_SAMPLER_3D,	//sampler3D
	SAMPLER_CUBE = GL_SAMPLER_CUBE,	//samplerCube
	SAMPLER_1D_SHADOW = GL_SAMPLER_1D_SHADOW,	//sampler1DShadow
	SAMPLER_2D_SHADOW = GL_SAMPLER_2D_SHADOW,	//sampler2DShadow
	SAMPLER_1D_ARRAY = GL_SAMPLER_1D_ARRAY,	//sampler1DArray
	SAMPLER_2D_ARRAY = GL_SAMPLER_2D_ARRAY,	//sampler2DArray
	SAMPLER_1D_ARRAY_SHADOW = GL_SAMPLER_1D_ARRAY_SHADOW,	//sampler1DArrayShadow
	SAMPLER_2D_ARRAY_SHADOW = GL_SAMPLER_2D_ARRAY_SHADOW,	//sampler2DArrayShadow
	SAMPLER_2D_MULTISAMPLE = GL_SAMPLER_2D_MULTISAMPLE, //sampler2DMS
	SAMPLER_2D_MULTISAMPLE_ARRAY = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,	//sampler2DMSArray
	SAMPLER_CUBE_SHADOW = GL_SAMPLER_CUBE_SHADOW,	//samplerCubeShadow
	SAMPLER_BUFFER = GL_SAMPLER_BUFFER,	//samplerBuffer
	SAMPLER_2D_RECT = GL_SAMPLER_2D_RECT,	//sampler2DRect
	SAMPLER_2D_RECT_SHADOW = GL_SAMPLER_2D_RECT_SHADOW,	//sampler2DRectShadow
	INT_SAMPLER_1D = GL_INT_SAMPLER_1D,	//isampler1D
	INT_SAMPLER_2D = GL_INT_SAMPLER_2D,	//isampler2D
	INT_SAMPLER_3D = GL_INT_SAMPLER_3D,	//isampler3D
	INT_SAMPLER_CUBE = GL_INT_SAMPLER_CUBE,	//isamplerCube
	INT_SAMPLER_1D_ARRAY = GL_INT_SAMPLER_1D_ARRAY,	//isampler1DArray
	INT_SAMPLER_2D_ARRAY = GL_INT_SAMPLER_2D_ARRAY,	//isampler2DArray
	INT_SAMPLER_2D_MULTISAMPLE = GL_INT_SAMPLER_2D_MULTISAMPLE,	//isampler2DMS
	INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,	//isampler2DMSArray
	INT_SAMPLER_BUFFER = GL_INT_SAMPLER_BUFFER,	//isamplerBuffer
	INT_SAMPLER_2D_RECT = GL_INT_SAMPLER_2D_RECT,	//isampler2DRect
	UNSIGNED_INT_SAMPLER_1D = GL_UNSIGNED_INT_SAMPLER_1D,	//usampler1D
	UNSIGNED_INT_SAMPLER_2D = GL_UNSIGNED_INT_SAMPLER_2D,	//usampler2D
	UNSIGNED_INT_SAMPLER_3D = GL_UNSIGNED_INT_SAMPLER_3D,	//usampler3D
	UNSIGNED_INT_SAMPLER_CUBE = GL_UNSIGNED_INT_SAMPLER_CUBE,	//usamplerCube
	UNSIGNED_INT_SAMPLER_1D_ARRAY = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,	//usampler2DArray
	UNSIGNED_INT_SAMPLER_2D_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,	//usampler2DArray
	UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,	//usampler2DMS
	UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,	//usampler2DMSArray
	UNSIGNED_INT_SAMPLER_BUFFER = GL_UNSIGNED_INT_SAMPLER_BUFFER,	//usamplerBuffer
	UNSIGNED_INT_SAMPLER_2D_RECT = GL_UNSIGNED_INT_SAMPLER_2D_RECT,	//usampler2DRect
	IMAGE_1D = GL_IMAGE_1D,	//image1D
	IMAGE_2D = GL_IMAGE_2D,	//image2D
	IMAGE_3D = GL_IMAGE_3D,	//image3D
	MAGE_2D_RECT = GL_IMAGE_2D_RECT,	//image2DRect
	MAGE_CUBE = GL_IMAGE_CUBE,	//imageCube
	MAGE_BUFFER = GL_IMAGE_BUFFER,	//imageBuffer
	MAGE_1D_ARRAY = GL_IMAGE_1D_ARRAY,	//image1DArray
	MAGE_2D_ARRAY = GL_IMAGE_2D_ARRAY,	//image2DArray
	IMAGE_2D_MULTISAMPLE = GL_IMAGE_2D_MULTISAMPLE,	//image2DMS
	IMAGE_2D_MULTISAMPLE_ARRAY = GL_IMAGE_2D_MULTISAMPLE_ARRAY,	//image2DMSArray
	INT_IMAGE_1D = GL_INT_IMAGE_1D,	//iimage1D
	INT_IMAGE_2D = GL_INT_IMAGE_2D,	//iimage2D
	INT_IMAGE_3D = GL_INT_IMAGE_3D,	//iimage3D
	INT_IMAGE_2D_RECT = GL_INT_IMAGE_2D_RECT,	//iimage2DRect
	INT_IMAGE_CUBE = GL_INT_IMAGE_CUBE,	//iimageCube
	INT_IMAGE_BUFFER = GL_INT_IMAGE_BUFFER,	//iimageBuffer
	INT_IMAGE_1D_ARRAY = GL_INT_IMAGE_1D_ARRAY,	//iimage1DArray
	INT_IMAGE_2D_ARRAY = GL_INT_IMAGE_2D_ARRAY,	//iimage2DArray
	INT_IMAGE_2D_MULTISAMPLE = GL_INT_IMAGE_2D_MULTISAMPLE,	//iimage2DMS
	INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,	//iimage2DMSArray
	UNSIGNED_INT_IMAGE_1D = GL_UNSIGNED_INT_IMAGE_1D,	//uimage1D
	UNSIGNED_INT_IMAGE_2D = GL_UNSIGNED_INT_IMAGE_2D,	//uimage2D
	UNSIGNED_INT_IMAGE_3D = GL_UNSIGNED_INT_IMAGE_3D,	//uimage3D
	UNSIGNED_INT_IMAGE_2D_RECT = GL_UNSIGNED_INT_IMAGE_2D_RECT,	//uimage2DRect
	UNSIGNED_INT_IMAGE_CUBE = GL_UNSIGNED_INT_IMAGE_CUBE,	//uimageCube
	UNSIGNED_INT_IMAGE_BUFFER = GL_UNSIGNED_INT_IMAGE_BUFFER,	//uimageBuffer
	UNSIGNED_INT_IMAGE_1D_ARRAY = GL_UNSIGNED_INT_IMAGE_1D_ARRAY,	//uimage1DArray
	UNSIGNED_INT_IMAGE_2D_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_ARRAY,	//uimage2DArray
	UNSIGNED_INT_IMAGE_2D_MULTISAMPLE = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,	//uimage2DMS
	UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,	//uimage2DMSArray
	UNSIGNED_INT_ATOMIC_COUNTER	= GL_UNSIGNED_INT_ATOMIC_COUNTER	//atomic_uint
};

/**
 * [Fixed] you must call this func at some time
 * [Optional] you call choose to call this func and remember to call all associated funcs
 * 
 * opengl org obj, which include diff shader stages
 * and in our logic, we do not choose a multiprogram solution
 * 
 * 
 */
class gl_program final : public gl_object, public std::enable_shared_from_this<gl_program>{
public:
	gl_program();
    gl_program(const gl_program&) = delete;
    gl_program& operator=(const gl_program&) = delete;

    ~gl_program() override;

public:

	/**
	 * once you install these component, you have no chance to remove or add them until the program destroyed
	 * load shaders code, compile shaders, attach shaders to program and link program
	 * validate program
	 *
	 * (0) program creation : shaders compilation
	 * (1) pre-link
	 * (2) link
	 * (3) introspection
	 * (4) state setting
	 */
	void construct(const std::vector<std::pair<std::string, gl_shader_type>>& shaders)
    {
        std::vector<std::uint32_t> _shader_handles;
        for (const auto& shader : shaders)
        {
            std::uint32_t _shader_handle = glCreateShader(static_cast<std::uint32_t>(shader.second));
            glAttachShader(_handle, _shader_handle);
            _shader_handles.push_back(_shader_handle);
        }

        // pre-link
        glBindAttribLocation(_handle, 0, ""); // input
        glBindFragDataLocation(_handle, 0, ""); // output
        //glTransformFeedbackVaryings(_handle, 10, {"", ""}, GL_INTERLEAVED_ATTRIBS );
        // link
        glLinkProgram(_handle);

        // check the program state
        if (!is_linked())
        {
            std::int32_t _log_length = info_log_length();
            std::vector<char> _log;
            _log.resize(_log_length);
            glGetProgramInfoLog(_handle, _log_length, nullptr, _log.data());
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << _log_length << std::endl;
            glValidateProgram(_handle);
        }
        std::cout << "[program is linked.]" << std::endl;

    }

public:

    /*
     * check the program state, and bind the program to current context,
     * there is only one program can be bound to context at the same time
     * */
    void enable()
    {
	    if(glIsProgram(_handle))
        {
            glUseProgram(_handle);
        }
    }

    /*
     * unbind the program from current context
     * */
	void disable()
    {
	    if(glIsProgram(_handle))
	        glUseProgram(0);

        glValidateProgram(_handle);
    }

public: // query
    // glGetActiveAtomicCounterBufferiv

    // glGetActiveAttrib
    // glGetAttribLocation

    // glGetActiveSubroutineName
    // glGetSubroutineIndex

    // glGetActiveSubroutineUniform
    // glGetActiveSubroutineUniformName
    // glGetSubroutineUniformLocation
    // glGetUniformSubroutine

    // glGetActiveUniform
    // glGetActiveUniformName
    // glGetActiveUniforms
    // glGetActiveUniformsiv
    // glGetUniformIndices
    // glGetUniformLocation
    // glGetUniform

    // glGetUniformBlockIndex
    // glGetActiveUniformBlock
    // glGetActiveUniformBlockName

    // glGetFragDataIndex
    // glGetFragDataLocation

    // glGetTransformFeedbackVarying


public:

    void get_interface() const noexcept
    {
        //glGetProgramInterfaceiv(_handle, GL_TRANSFORM_FEEDBACK, GL_ACTIVE_RESOURCES, );
    }

    // glGetProgramResource
    void get_resource() const noexcept
    {
        //glGetProgramResourceiv(_handle, GL_ATOMIC_COUNTER_BUFFER, -1, 100, {}, 100,  );
    }

    /*
     * query the index of a named resource within a program
     * returns the uint index assigned to a resource named name in the interface type programInterface of program object program.
     * 4.3
     * @programInterface :
     *  A token identifying the interface within program containing the resource named name.
     *
     *  UNIFORM,
     *  UNIFORM_BLOCK,
     *  SHADER_STORAGE_BLOCK,
     *  BUFFER_VARIABLE,
     *
     *  PROGRAM_INPUT,
     *  PROGRAM_OUTPUT,
     *  TRANSFORM_FEEDBACK_VARYING,
     *  TRANSFORM_FEEDBACK_BUFFER,
     *
     *  VERTEX_SUBROUTINE,
     *  TESS_CONTROL_SUBROUTINE, TESS_EVALUATION_SUBROUTINE,
     *  GEOMETRY_SUBROUTINE,
     *  FRAGMENT_SUBROUTINE,
     *  COMPUTE_SUBROUTINE
     *
     *  VERTEX_SUBROUTINE_UNIFORM,
     *  TESS_CONTROL_SUBROUTINE_UNIFORM, TESS_EVALUATION_SUBROUTINE_UNIFORM,
     *  GEOMETRY_SUBROUTINE_UNIFORM,
     *  FRAGMENT_SUBROUTINE_UNIFORM,
     *  COMPUTE_SUBROUTINE_UNIFORM
     *
     * @name : The name of the resource to query the index of.
     * */
    bool get_resource_index(gl_program_interface interface, const char* name, std::uint32_t& out_index) const noexcept
    {
        if(interface == gl_program_interface::TRANSFORM_FEEDBACK_BUFFER ||
        interface == gl_program_interface::ATOMIC_COUNTER_BUFFER) return false;
        out_index = glGetProgramResourceIndex(_handle, static_cast<GLenum>(interface), name);
        return true;
    }

    /*
     * query the index of a named resource within a program
     * returns the uint index assigned to a resource named name in the interface type programInterface of program object program.
     * 4.3
     * @programInterface :
     *  A token identifying the interface within program containing the resource named name.
     *
     *  UNIFORM,
     *
     *  PROGRAM_INPUT,
     *  PROGRAM_OUTPUT,
     *  TRANSFORM_FEEDBACK_BUFFER,
     *
     *  VERTEX_SUBROUTINE_UNIFORM,
     *  TESS_CONTROL_SUBROUTINE_UNIFORM, TESS_EVALUATION_SUBROUTINE_UNIFORM,
     *  GEOMETRY_SUBROUTINE_UNIFORM,
     *  FRAGMENT_SUBROUTINE_UNIFORM,
     *  COMPUTE_SUBROUTINE_UNIFORM
     *
     * @name : The name of the resource to query the index of.
     * */
    bool get_resource_location(gl_program_interface interface, const char* name, std::int32_t& out_location) const noexcept
    {
        out_location = glGetProgramResourceLocation(_handle, static_cast<GLenum>(interface), name);
        return true;
    }

    /*
     * get program output var index by specified name, return -1 if it does not exist
     * query the fragment color index of a named variable within a program
     * @programInterface : A token identifying the interface within program containing the resource named name.
     * @name : The name of the resource to query the location of
     *
     *  GL_PROGRAM_OUTPUT
     *
     * The value -1 will be returned if an error occurs, if name does not identify an active variable on programInterface,
     * or if name identifies an active variable that does not have a valid location assigned, as described above.
     * The locations returned by these commands are the same locations returned
     * when querying the GL_LOCATION and GL_LOCATION_INDEX resource properties.
     * */
    bool get_resource_location_index(const char* name, std::int32_t& out_location_index) const noexcept
    {
        out_location_index = glGetProgramResourceLocationIndex(_handle, GL_PROGRAM_OUTPUT, name);
        return true;
    }

    /*
     * query the index of a named resource within a program
     * returns the uint index assigned to a resource named name in the interface type programInterface of program object program.
     * 4.3
     * @programInterface :
     *  A token identifying the interface within program containing the resource named name.
     *
     *  UNIFORM,
     *  UNIFORM_BLOCK,
     *  SHADER_STORAGE_BLOCK,
     *  BUFFER_VARIABLE,
     *
     *  PROGRAM_INPUT,
     *  PROGRAM_OUTPUT,
     *  TRANSFORM_FEEDBACK_VARYING,
     *
     *  VERTEX_SUBROUTINE,
     *  TESS_CONTROL_SUBROUTINE, TESS_EVALUATION_SUBROUTINE,
     *  GEOMETRY_SUBROUTINE,
     *  FRAGMENT_SUBROUTINE,
     *  COMPUTE_SUBROUTINE
     *
     *
     *  VERTEX_SUBROUTINE_UNIFORM,
     *  TESS_CONTROL_SUBROUTINE_UNIFORM, TESS_EVALUATION_SUBROUTINE_UNIFORM,
     *  GEOMETRY_SUBROUTINE_UNIFORM,
     *  FRAGMENT_SUBROUTINE_UNIFORM,
     *  COMPUTE_SUBROUTINE_UNIFORM
     *
     * @name : The name of the resource to query the index of.
     * */
    std::string resource_name(gl_program_interface interface, std::uint32_t index) const noexcept
    {
        std::int32_t _length = 0;
        glGetProgramResourceName(_handle, static_cast<GLenum>(interface), index, 0, &_length, nullptr);
        char* name;
        glGetProgramResourceName(_handle, static_cast<GLenum>(interface), index, _length, nullptr, name);
        return std::string(name);
    }



    // glGetProgramStageiv
    std::int32_t stage_active_subroutine_uniforms_num(gl_shader_type shader_type)
    {
        GLint param;
        glGetProgramStageiv(_handle, static_cast<GLenum>(shader_type), GL_ACTIVE_SUBROUTINE_UNIFORMS, &param);
        return param;
    }

    std::int32_t stage_active_subroutine_uniform_locations_num(gl_shader_type shader_type)
    {
        GLint param;
        glGetProgramStageiv(_handle, static_cast<GLenum>(shader_type), GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, &param);
        return param;
    }

    std::int32_t stage_active_subroutines_num(gl_shader_type shader_type)
    {
        GLint param;
        glGetProgramStageiv(_handle, static_cast<GLenum>(shader_type), GL_ACTIVE_SUBROUTINES, &param);
        return param;
    }

    std::int32_t stage_active_subroutine_uniform_name_max_length(gl_shader_type shader_type)
    {
        GLint param;
        glGetProgramStageiv(_handle, static_cast<GLenum>(shader_type), GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, &param);
        return param;
    }

    std::int32_t stage_active_subroutine_name_max_length(gl_shader_type shader_type)
    {
        GLint param;
        glGetProgramStageiv(_handle, static_cast<GLenum>(shader_type), GL_ACTIVE_SUBROUTINE_MAX_LENGTH, &param);
        return param;
    }
    // glGetProgramStageiv

    //glGetShaderPrecisionFormat

    //glGetShaderPrecisionFormat




public: // glGetProgramiv
    /*
     * if program is currently flagged for deletion, return true
     * */
    bool is_deleted() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_DELETE_STATUS, &param);
        return param == GL_TRUE;
	}

    /*
     * if the last link operation on program was successful, return true
     * */
    bool is_linked() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_LINK_STATUS, &param);
        return param == GL_TRUE;
    }

    /*
     * if the last validation operation on program was successful, return true
     * */
    bool is_valid() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_VALIDATE_STATUS, &param);
        return param == GL_TRUE;
    }

    /*
     * returns the number of characters in the information log for program including the null termination character
     * (i.e., the size of the character buffer required to store the information log).
     * If program has no information log, a value of 0 is returned.
     * */
    std::int32_t info_log_length() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &param);
        return param;
    }

    /*
     * returns the number of shader objects attached to program
     * */
    std::int32_t attached_shaders_num() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_ATTACHED_SHADERS, &param);
        return param;
    }

    /*
     * returns the number of active attribute atomic counter buffers used by program
     * */
    std::int32_t active_atomic_counter_buffers_num() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_ACTIVE_ATOMIC_COUNTER_BUFFERS, &param);
        return param;
    }

    /*
     * returns the number of active attribute variables for program
     * */
    std::int32_t active_attributes_num() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTES, &param);
        return param;
    }

    /*
     * returns the length of the longest active attribute name for program, including the null termination character
     * (i.e., the size of the character buffer required to store the longest attribute name).
     * If no active attributes exist, 0 is returned.
     * */
    std::int32_t active_attribute_name_max_length() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &param);
        return param;
    }

    /*
     * returns the number of active uniform variables for program
     * */
    std::int32_t active_uniforms_num() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_ACTIVE_UNIFORMS, &param);
        return param;
    }

    /*
     * params returns the length of the longest active uniform variable name for program, including the null termination character
     * (i.e., the size of the character buffer required to store the longest uniform variable name).
     * If no active uniform variables exist, 0 is returned.
     * */
    std::int32_t active_uniform_name_max_length() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &param);
        return param;
    }

    /*
     *
     * */
    std::int32_t active_uniform_blocks_num() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_ACTIVE_UNIFORM_BLOCKS, &param);
        return param;
    }

    /*
     *
     * */
    std::int32_t active_uniform_block_name_max_length() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &param);
        return param;
    }


    /*
     * params returns an array of three integers containing the local work group size of the compute program as specified by its input layout qualifier(s).
     * program must be the name of a program object that has been previously linked successfully and contains a binary for the compute shader stage.
     * */
    std::int32_t compute_work_group_size() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_COMPUTE_WORK_GROUP_SIZE, &param);
        return param;
    }

    /*
     * returns the length of the program binary, in bytes that will be returned by a call to glGetProgramBinary.
     * When a program is not linked, its program binary length is zero.
     * */
    std::int32_t program_binary_length() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_PROGRAM_BINARY_LENGTH, &param);
        return param;
    }

    /*
     * returns the number of varying variables to capture in transform feedback mode for the program
     * */
    std::int32_t transform_feedback_varyings_num() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_TRANSFORM_FEEDBACK_VARYINGS, &param);
        return param;
    }

    /*
     * returns the length of the longest variable name to be used for transform feedback, including the null-terminator.
     * */
    std::int32_t transform_feedback_varying_name_max_length() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH, &param);
        return param;
    }

    /*
     * returns a symbolic constant indicating the buffer mode used when transform feedback is active.
     * This may be SEPARATE_ATTRIBS or INTERLEAVED_ATTRIBS.
     * */
    gl_transform_feedback_buffer_mode transform_feedback_buffer_mode() const noexcept{
        GLint param;
        glGetProgramiv(_handle, GL_TRANSFORM_FEEDBACK_BUFFER_MODE, &param);
        return static_cast<gl_transform_feedback_buffer_mode>(param);
    }

    /*
     * returns the maximum number of vertices that the geometry shader in program will output
     * */
    std::int32_t geometry_vertices_max_num() const noexcept
    {
        GLint param;
        glGetProgramiv(_handle, GL_GEOMETRY_VERTICES_OUT, &param);
        return param;
    }

    /*
     * returns a symbolic constant indicating the primitive type accepted as input to the geometry shader contained in program.
     * */
    gl_primitive_type geometry_input_type() const noexcept{
        GLint param;
        glGetProgramiv(_handle, GL_GEOMETRY_INPUT_TYPE, &param);
        return static_cast<gl_primitive_type>(param);
    }

    /*
     * returns a symbolic constant indicating the primitive type that will be output by the geometry shader contained in program.
     * */
    gl_primitive_type geometry_output_type() const noexcept{
        GLint param;
        glGetProgramiv(_handle, GL_GEOMETRY_OUTPUT_TYPE, &param);
        return static_cast<gl_primitive_type>(param);
    }

public:

    std::int32_t active_atomic_counter_buffer_binding() const noexcept
    {
        GLuint _buffer_index = 0;
        if(_buffer_index < 0 || _buffer_index >= active_atomic_counter_buffers_num()) return -1;
        GLint param;
        glGetActiveAtomicCounterBufferiv(_handle, _buffer_index, GL_ATOMIC_COUNTER_BUFFER_BINDING, &param);
        return param;
    }

    std::int32_t active_atomic_counter_buffer_data_size() const noexcept
    {
        GLuint _buffer_index = 0;
        if(_buffer_index < 0 || _buffer_index >= active_atomic_counter_buffers_num()) return -1;
        GLint param;
        glGetActiveAtomicCounterBufferiv(_handle, _buffer_index, GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE, &param);
        return param;
    }

    std::int32_t active_atomic_counter_buffer_counters_num() const noexcept
    {
        std::uint32_t _buffer_index = 0;
        if(_buffer_index < 0 || _buffer_index >= active_atomic_counter_buffers_num()) return -1;
        GLint param;
        glGetActiveAtomicCounterBufferiv(_handle, _buffer_index, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS, &param);
        return param;
    }

    std::vector<std::int32_t> active_atomic_counter_buffer_counters_indices() const noexcept
    {
        std::uint32_t _buffer_index = 0;
        if(_buffer_index < 0 || _buffer_index >= active_atomic_counter_buffers_num()) return {};
        std::int32_t _counters_num = active_atomic_counter_buffer_counters_num();
        std::vector<std::int32_t> indices(_counters_num);
        glGetActiveAtomicCounterBufferiv(_handle, _buffer_index, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES, indices.data());
        return indices;
    }

    bool is_atomic_counter_buffer_referenced_by_vertex_shader() const noexcept
    {
        std::uint32_t _buffer_index = 0;
        if(_buffer_index < 0 || _buffer_index >= active_atomic_counter_buffers_num()) return -1;
        GLint param;
        glGetActiveAtomicCounterBufferiv(_handle, _buffer_index, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER, &param);
        return param == GL_TRUE;
    }

    bool is_atomic_counter_buffer_referenced_by_tess_control_shader() const noexcept
    {
        std::uint32_t _buffer_index = 0;
        if(_buffer_index < 0 || _buffer_index >= active_atomic_counter_buffers_num()) return -1;
        GLint param;
        glGetActiveAtomicCounterBufferiv(_handle, _buffer_index, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER, &param);
        return param == GL_TRUE;
    }

    bool is_atomic_counter_buffer_referenced_by_tess_evaluation_shader() const noexcept
    {
        std::uint32_t _buffer_index = 0;
        if(_buffer_index < 0 || _buffer_index >= active_atomic_counter_buffers_num()) return -1;
        GLint param;
        glGetActiveAtomicCounterBufferiv(_handle, _buffer_index, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER, &param);
        return param == GL_TRUE;
    }

    bool is_atomic_counter_buffer_referenced_by_geometry_shader() const noexcept
    {
        std::uint32_t _buffer_index = 0;
        if(_buffer_index < 0 || _buffer_index >= active_atomic_counter_buffers_num()) return -1;
        GLint param;
        glGetActiveAtomicCounterBufferiv(_handle, _buffer_index, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER, &param);
        return param == GL_TRUE;
    }

    bool is_atomic_counter_buffer_referenced_by_fragment_shader() const noexcept
    {
        std::uint32_t _buffer_index = 0;
        if(_buffer_index < 0 || _buffer_index >= active_atomic_counter_buffers_num()) return -1;
        GLint param;
        glGetActiveAtomicCounterBufferiv(_handle, _buffer_index, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER, &param);
        return param == GL_TRUE;
    }

    bool is_atomic_counter_buffer_referenced_by_compute_shader() const noexcept
    {
        std::uint32_t _buffer_index = 0;
        if(_buffer_index < 0 || _buffer_index >= active_atomic_counter_buffers_num()) return -1;
        GLint param;
        glGetActiveAtomicCounterBufferiv(_handle, _buffer_index, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER, &param);
        return param == GL_TRUE;
    }





public: // glGetActiveAttrib

    struct gl_attribute_info
    {
        std::int32_t size;
        std::uint32_t type;
        std::string name;
    };

    gl_attribute_info active_attribute(std::uint32_t index)
    {
        gl_attribute_info _info;
        glGetActiveAttrib(_handle, index, active_attribute_name_max_length(), nullptr, &_info.size, &_info.type, _info.name.data());
        return _info;
    }

public:

    /*
     * Returns the location of an attribute variable
     * */
    std::int32_t attribute_location(const char* name) const noexcept
    {
        return glGetAttribLocation(_handle, name);
    }


public:

    /*
     * query the bindings of color indices to user-defined varying out variables
     * */
    std::int32_t fragment_data_index(const char* name) const noexcept
    {
        return glGetFragDataIndex(_handle, name);
    }

    /*
     *  query the bindings of color numbers to user-defined varying out variables
     * */
    std::int32_t fragment_data_location(const char* name) const noexcept
    {
        return glGetFragDataLocation(_handle, name);
    }


public:

    std::uint32_t query_uniform_block_index(const char* name)
    {
        return glGetUniformBlockIndex(_handle, name);
    }



    //
    std::int32_t attribute_location(const char* name)
    {
        return glGetAttribLocation(_handle, name);
    }

    void query()
    {
	    GLint param;

//
//	    glGetActiveSubroutineName();
//	    glGetActiveSubroutineUniformiv();
//	    glGetActiveSubroutineUniformName();
//
//	    glGetActiveUniform();
//	    glGetActiveUniformBlockName();
//	    glGetActiveUniformName();
//
//        glGetActiveUniformsiv();
//        //glGetAttribLocation();
//
//        glGetProgramStageiv();
//        glGetShaderPrecisionFormat();
//
//        glGetSubroutineIndex();
//        glGetSubroutineUniformLocation();
//
//        glGetTransformFeedbackVarying();
//        glGetUniformdv();
//        // etc
//        glGetUniformBlockIndex();
//        glGetUniformIndices();
//        glGetUniformLocation();
//        glGetUniformSubroutineuiv();

    }

    void set()
    {
//	    glActiveShaderProgram();
//	    glBindProgramPipeline();
//	    glProgramUniform1d();
//	    glProgramUniformMatrix2dv();
//	    glShaderStorageBlockBinding();
//	    glUniform1d();
//	    glUniformBlockBinding();
//	    glUniformMatrix2dv();
//	    glUniformSubroutinesuiv();
//	    glUseProgram();
    }

public:

    std::int32_t query_uniform_item(const char* item_name)
    {
        return glGetUniformLocation(_handle, item_name);
    }

    std::int32_t query_uniform_block_item(const char* block_item_name)
    {
        return glGetUniformBlockIndex(_handle, block_item_name);
    }

	void set_vertex_array(std::shared_ptr<class gl_vertex_array> vertex_array);

	void set_element_array_buffer(std::shared_ptr<class gl_element_array_buffer> element_array_buffer);

	void set_transform_feedback(std::shared_ptr<class gl_transform_feedback> transform_feedback);

	void add_uniform_buffer(std::shared_ptr<class gl_uniform_buffer> uniform_buffer);

	void add_shader_storage_buffer(std::shared_ptr<class gl_shader_storage_buffer> shader_storage_buffer);

	void add_atomic_counter_buffer(std::shared_ptr<class gl_atomic_counter_buffer> atomic_counter_buffer);

	void set_framebuffer(std::shared_ptr<class gl_framebuffer> framebuffer = nullptr);

	void set_commands(std::function<void(void)> commands_lambda);

public:

	std::shared_ptr<gl_vertex_array> get_vertex_array();

	std::shared_ptr<gl_element_array_buffer> get_element_array_buffer();

	std::shared_ptr<gl_transform_feedback> get_transform_feedback();

	std::shared_ptr<gl_uniform_buffer> get_uniform_buffer(std::uint32_t index);

	std::shared_ptr<gl_shader_storage_buffer> get_shader_storage_buffer(std::uint32_t index);

	std::shared_ptr<gl_atomic_counter_buffer> get_atomic_counter_buffer(std::uint32_t index);

	std::shared_ptr<gl_framebuffer> get_framebuffer();

public:

	void set_stencil_test()
	{
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilMask(GL_TRUE);
	}

	void enable_stencil_test()
	{
		glEnable(GL_STENCIL_TEST);
	}

	void disable_stencil_test()
	{
		glDisable(GL_STENCIL_TEST);
	}

	void set_depth_test()
	{
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glClearDepth(1.0f);
	}

	void enable_depth_test()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void disable_depth_test()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void set_alpha_test()
	{
		//glAlphaFunc();
	}

	void enable_alpha_test()
	{
		glEnable(GL_ALPHA_TEST);
	}

	void disable_alpha_test()
	{
		glDisable(GL_ALPHA_TEST);
	}
	
public:

	/**
	 * start render processing
	 */
	void render(std::float_t delta_time);

private:

	std::vector<std::shared_ptr<gl_shader>> _shaders;

	std::shared_ptr<gl_vertex_array> _vertex_array;
	
	std::shared_ptr<gl_element_array_buffer> _element_array_buffer;
	
	std::shared_ptr<gl_transform_feedback> _transform_feedback;
	
	std::vector<std::shared_ptr<gl_uniform_buffer>> _uniform_buffers;
	
	std::vector<std::shared_ptr<gl_shader_storage_buffer>> _shader_storage_buffers;
	
	std::vector<std::shared_ptr<gl_atomic_counter_buffer>> _atomic_counter_buffers;
	
	std::shared_ptr<gl_framebuffer> _framebuffer;
	
	static std::shared_ptr<gl_default_framebuffer> _default_framebuffer;
	
	std::function<void(void)> _commands_lambda;

private:
	//~ render begin
	void _tick_objects();
	void _install();
	void _enable();
	void _call_commands();
	void _disable();
	void _uninstall();
	//~ render end
private:

	// set only once time (when you first time setting the transform feedback)
	void _set_transform_feedback_varyings();

	// bind these persistent data to context (context is public)
	void _bind_vertex_array();
	void _bind_element_array_buffer();
	void _bind_transform_feedback();
	void _bind_uniform_buffers();
	void _bind_shader_storage_buffers();
	void _bind_atomic_counter_buffers();
	void _bind_framebuffer();
	void _bind_textures();

	void _launch_uniforms();

	// unbind these persistent data from context (you can not ensure that slots your have used will be overriden by next program)
	void _unbind_vertex_array()
	{
		glBindVertexArray(0);
	}
	void _unbind_element_array_buffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void _unbind_transform_feedback()
	{
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	}
	void _unbind_uniform_buffers()
	{
		// clear all uniform buffers binding is too expensive
		// use the stored ids
		for (std::int32_t i = 0; i < _uniform_buffers.size(); ++i)
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, i, 0);
		}
	}
	void _unbind_shader_storage_buffers()
	{
		for (std::int32_t i = 0; i < _shader_storage_buffers.size(); ++i)
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i, 0);
		}
	}
	void _unbind_atomic_counter_buffers()
	{
		for (std::uint32_t i = 0; i < _atomic_counter_buffers.size(); ++i)
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i, 0);
		}
	}
	void _unbind_framebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

public:

	void generate_uniform_buffer_layout(const std::string& block_name)
	{
		std::vector<GLchar*> _names = {};
		std::vector<GLuint> _indices(_names.size());
		std::vector<GLint> _offsets(_names.size());
		// get block size
		std::int32_t _block_size = 0;
		const auto _block_index = glGetUniformBlockIndex(_handle, block_name.c_str());
		glGetActiveUniformBlockiv(_handle, _block_index, GL_UNIFORM_BLOCK_DATA_SIZE, &_block_size);
		//glGetUniformIndices(_handle, _names.size(), _names.data(), _indices.data());
		glGetActiveUniformsiv(_handle, 4, _indices.data(), GL_UNIFORM_OFFSET, _offsets.data());
	}


	const std::int32_t get_uniform_buffer_block_size(const std::string block_name) const
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle,
			glGetUniformBlockIndex(_handle, block_name.c_str()),
			GL_UNIFORM_BLOCK_DATA_SIZE, &_value);
		return _value;
	}

	const std::int32_t get_uniform_buffer_item_offset(const std::string& name) const
	{
		const char* str = name.data();
		GLuint _index = 0;
		GLint _offset = 0;
		glGetUniformIndices(_handle, 1, &str, &_index);
		glGetActiveUniformsiv(_handle, 1, &_index, GL_UNIFORM_OFFSET, &_offset);
		return _offset;
	}


	const std::int32_t get_shader_storage_buffer_block_size() const
	{
		GLint _value = 0;
		_value = glGetProgramResourceIndex(_handle, GL_SHADER_STORAGE_BLOCK, "");
		return _value;
	}

	std::vector<std::int32_t> get_uniform_buffer_uniform_indices(const std::string& block_name)
	{
		GLint* _value = nullptr;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, _value);
		const auto _size = get_uniform_buffer_uniforms_num(block_name);

		std::vector<std::int32_t> _indices;
		for (std::int32_t i = 0; i < _size; ++i)
		{
			_indices.push_back(_value[i]);
		}

		return _indices;
	}

	std::int32_t get_uniform_buffer_block_name_length(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_NAME_LENGTH, &_value);
		return _value;
	}

	std::int32_t get_uniform_buffer_binding_index(const std::string& block_name)
	{
		GLint _value;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_BINDING, &_value);
		return _value;
	}

	std::int32_t get_uniform_buffer_uniforms_num(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &_value);
		return _value;
	}

	bool is_uniform_buffer_referred_by_vert_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, &_value);
		return _value == GL_TRUE;
	}
	bool is_uniform_buffer_referred_by_tesc_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER, &_value);
		return _value == GL_TRUE;
	}
	bool is_uniform_buffer_referred_by_tese_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER, &_value);
		return _value == GL_TRUE;
	}
	bool is_uniform_buffer_referred_by_geom_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, &_value);
		return _value == GL_TRUE;
	}
	bool is_uniform_buffer_referred_by_frag_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, &_value);
		return _value == GL_TRUE;
	}
	bool is_uniform_buffer_referred_by_comp_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle,
                                  glGetUniformBlockIndex(_handle, block_name.c_str()),
                                  GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER, &_value
                                  );
		return _value == GL_TRUE;
	}
 
};

#endif
