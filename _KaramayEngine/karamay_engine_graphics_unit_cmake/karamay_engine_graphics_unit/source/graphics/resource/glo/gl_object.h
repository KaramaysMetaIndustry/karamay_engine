#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include "graphics/glsl/glsl_class.h"

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
