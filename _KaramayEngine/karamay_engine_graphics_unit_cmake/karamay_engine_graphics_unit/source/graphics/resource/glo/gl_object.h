#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include "graphics/glsl/glsl_class.h"
#include "graphics/resource/sync/gl_sync.h"

enum gl_error : GLenum
{
    INVALID_ENUM = GL_INVALID_ENUM,
    INVALID_VALUE = GL_INVALID_VALUE,
    INVALID_OPERATION = GL_INVALID_OPERATION,
    STACK_OVERFLOW = GL_STACK_OVERFLOW,
    STACK_UNDERFLOW = GL_STACK_UNDERFLOW,
    OUT_OF_MEMORY = GL_OUT_OF_MEMORY,
    INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION,
    CONTEXT_LOST = GL_CONTEXT_LOST,
    TABLE_TOO_LARGE = GL_TABLE_TOO_LARGE
};

enum class gl_object_type
{
    BUFFER_OBJ = GL_BUFFER,
    SHADER_OBJ = GL_SHADER,
    PROGRAM_OBJ = GL_PROGRAM,
    VERTEX_ARRAY_OBJ = GL_VERTEX_ARRAY,
    QUERY_OBJ = GL_QUERY,
    PROGRAM_PIPELINE_OBJ = GL_PROGRAM_PIPELINE,
    TRANSFORM_FEEDBACK_OBJ = GL_TRANSFORM_FEEDBACK,
    SAMPLER_OBJ = GL_SAMPLER,
    TEXTURE_OBJ = GL_TEXTURE,
    RENDERBUFFER_OBJ = GL_RENDERBUFFER,
    FRAMEBUFFER_OBJ = GL_FRAMEBUFFER
};

enum class internal_format : GLenum
{
    R8 = GL_R8,
    R16 = GL_R16,
    R16F = GL_R16F,
    R32F = GL_R32F,
    R8I = GL_R8I,
    R16I = GL_R16I,
    R32I = GL_R32I,
    R8UI = GL_R8UI,
    R16UI = GL_R16UI,
    R32UI = GL_R32UI,
    RG8 = GL_RG8,
    RG16 = GL_RG16,
    RG16F = GL_RG16F,
    RG32F = GL_RG32F,
    RG8I = GL_RG8I,
    RG16I = GL_RG16I,
    RG32I = GL_RG32I,
    RG8UI = GL_RG8UI,
    RG16UI = GL_RG16UI,
    RG32UI = GL_RG32UI,
    RGB32F = GL_RGB32F,
    RGB32I = GL_RGB32I,
    RGB32UI = GL_RGB32UI,
    RGBA8 = GL_RGBA8,
    RGBA16 = GL_RGBA16,
    RGBA16F = GL_RGBA16F,
    RGBA32F = GL_RGBA32F,
    RGBA8I = GL_RGBA8I,
    RGBA16I = GL_RGBA16I,
    RGBA32I = GL_RGBA32I,
    RGBA8UI = GL_RGBA8UI,
    RGBA16UI = GL_RGBA16UI,
    RGBA32UI = GL_RGBA32UI
};

enum class format : GLenum
{
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    BGR = GL_BGR,
    RGBA = GL_RGBA,
    BGRA = GL_BGRA,
    RED_INTEGER = GL_RED_INTEGER,
    RG_INTEGER = GL_RG_INTEGER,
    RGB_INTEGER = GL_RGB_INTEGER,
    BGR_INTEGER = GL_BGR_INTEGER,
    RGBA_INTEGER = GL_RGBA_INTEGER,
    BGRA_INTEGER = GL_BGRA_INTEGER,
    STENCIL_INDEX = GL_STENCIL_INDEX,
    DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    DEPTH_STENCIL = GL_DEPTH_STENCIL
};

enum class data_type : GLenum
{
    HALF_FLOAT = GL_HALF_FLOAT,
    FLOAT = GL_FLOAT,

    BYTE = GL_BYTE,
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    SHORT = GL_SHORT,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    INT = GL_INT,
    UNSIGNED_INT = GL_UNSIGNED_INT,

    UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
    UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
    UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
    UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
    UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
    UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
    UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
    UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
    UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
};


class gl_object{
protected:
    gl_object() = delete;
	gl_object(gl_object_type object_type) : _handle(0), _type(object_type)
	{}
	
    virtual ~gl_object() = default;

	std::uint32_t _handle;

    gl_object_type _type;

public:

    static void _throw_errors(const std::string& func_name)
    {
        std::vector<gl_error> _errors;
        gl_error err;
        while((err = static_cast<gl_error>(glGetError())) != GL_NO_ERROR)
        {
            _errors.push_back(err);
        }
        if(_errors.size())
        {
            std::cout<<func_name<<": ["<<std::endl;
            for(auto _error : _errors)
            {
                std::cout<<"      ";
                switch (_error) {
                    case INVALID_ENUM:std::cout<<"INVALID_ENUM"<<std::endl;
                        break;
                    case INVALID_VALUE:std::cout<<"INVALID_VALUE"<<std::endl;
                        break;
                    case INVALID_OPERATION:std::cout<<"INVALID_OPERATION"<<std::endl;
                        break;
                    case STACK_OVERFLOW:std::cout<<"STACK_OVERFLOW"<<std::endl;
                        break;
                    case STACK_UNDERFLOW:std::cout<<"STACK_UNDERFLOW"<<std::endl;
                        break;
                    case OUT_OF_MEMORY:std::cout<<"OUT_OF_MEMORY"<<std::endl;
                        break;
                    case INVALID_FRAMEBUFFER_OPERATION:std::cout<<"INVALID_FRAMEBUFFER_OPERATION"<<std::endl;
                        break;
                    case CONTEXT_LOST:std::cout<<"CONTEXT_LOST"<<std::endl;
                        break;
                    case TABLE_TOO_LARGE:std::cout<<"TABLE_TOO_LARGE"<<std::endl;
                        break;
                }
            }
            std::cout<<"]"<<std::endl;
        }
    }

    virtual std::uint8_t _check_object_validation() const { return 0;}

public:
	
	[[nodiscard]] std::uint32_t get_handle() const { return _handle; }

    void sync()
    {
//        GLsync _sync;
//        glClientWaitSync();
//        glWaitSync();
//        glFlush();
//        glFinish();
//        glFenceSync();
//        glMemoryBarrier(0);

    }
};

#endif

